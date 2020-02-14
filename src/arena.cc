/**
 * @file arena.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>

#include "src/arena.h"
#include "src/robot.h"
#include "src/player.h"
#include "src/obstacle.h"
#include "src/event_collision.h"
#include "src/event_proximity.h"
#include "src/event_entity_type.h"
#include "src/arena_params.h"
#include "src/recharge_station.h"
#include "src/home_base.h"
#include "src/event_recharge.h"
#include "src/event_command.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
// TODO: Refactor code
/**
 * @brief Arena constructor
 * @param params Parameters needed to instantiate an arena
 */
Arena::Arena(const struct arena_params* const params) :
	player_(new Player(&params->player)),
	recharge_station_(new RechargeStation(params->recharge_station.radius,
	                                      params->recharge_station.pos,
	                                      params->recharge_station.color)),
	home_base_(new HomeBase(&params->home_base)), entities_(), mobile_entities_(),
	robot_entities_(), superbot_entities_(), n_superbots_(0),
	n_obstacles_(params->n_obstacles), n_robots_(params->n_robots),
	x_dim_(params->x_dim), y_dim_(params->y_dim), n_players_(1) {

	home_base_->set_heading_angle(75);
	player_->set_heading_angle(37);
	entities_.push_back(player_);
	mobile_entities_.push_back(player_);
	entities_.push_back(recharge_station_);
	entities_.push_back(home_base_);
	mobile_entities_.push_back(home_base_);

	// initializes obstacles
	for (size_t i = 0; i < n_obstacles_; ++i) {
		entities_.push_back(new Obstacle(
					    params->obstacles[i].radius,
					    params->obstacles[i].pos,
					    params->obstacles[i].color));
	}

	// initializes robots
	for (size_t i = 0; i < n_robots_; ++i) {
		Robot * r = new Robot(&params->robots[i]);
		entities_.push_back(r);
		mobile_entities_.push_back(r);
		robot_entities_.push_back(r);
	}

	// initializes a superbot for each robot
	for (size_t i = 0; i < n_robots_; ++i) {
		SuperBot * s = new SuperBot(&params->superbots[i]);
		superbot_entities_.push_back(s);
	}
}

/**
 * @brief Arena destructor
 */
Arena::~Arena(void) {
	for (auto ent : entities_) {
		delete ent;
	}
}
/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Reset all entities in the arena, effectively restarting the game.
 */
void Arena::Reset(void) {
	// erase all remaining robots from the entity vectors then push all back on
	for (auto ent : robot_entities_) {
		entities_.erase(std::remove(entities_.begin(), entities_.end(), ent), entities_.end());
		mobile_entities_.erase(std::remove(mobile_entities_.begin(),
		                                   mobile_entities_.end(), ent), mobile_entities_.end());
		entities_.push_back(ent);
		mobile_entities_.push_back(ent);
	}

	// erase all remaining superbots from entity vectors so they aren't drawn or updated
	for (auto ent : superbot_entities_) {
		entities_.erase(std::remove(entities_.begin(), entities_.end(), ent), entities_.end());
		mobile_entities_.erase(std::remove(mobile_entities_.begin(),
		                                   mobile_entities_.end(), ent), mobile_entities_.end());
	}

	// Reset all entities to newly minted state
	for (auto ent : entities_) {
		ent->Reset();
	}
}

/**
 * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
 * @return std::vector<Obstacle*> A vector containing the obstacles in the arena
 */
std::vector<Obstacle*> Arena::obstacles(void) {
	std::vector<Obstacle*> res;
	for (auto ent : entities_) {
		Obstacle* o = dynamic_cast<Obstacle*>(ent);
		if (o) {
			res.push_back(o);
		}
	}
	return res;
}

/**
 * @brief Get a list of all robots.
 * @return std::vector<Robot*> A vector containing the Robots in the arena
 */
std::vector<Robot*> Arena::robots(void) {
	std::vector<Robot*> res;
	for (auto ent : mobile_entities_) {
		Robot* o = dynamic_cast<Robot*>(ent);
		if (o) {
			res.push_back(o);
		}
	}
	return res;
}

/**
 * @brief Get a list of all Superbots.
 * @return std::vector<SuperBot*> A vector containing the Superbots in the arena
 */
std::vector<SuperBot*> Arena::superbots(void) {
	std::vector<SuperBot*> res;
	for (auto ent : mobile_entities_) {
		SuperBot* o = dynamic_cast<SuperBot*>(ent);
		if (o) {
			res.push_back(o);
		}
	}
	return res;
}

/**
 * @brief Advance the simulation by the specified # of steps.
 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
 */
int Arena::AdvanceTime(void) {
	for (size_t i = 0; i < 1; ++i) {
		return UpdateEntitiesTimestep();
	}
	return 2;
}

/**
 * @brief Returns the level of the player battery.
 * @return double Player's battery level
 */
double Arena::get_player_battery_level(void) {
	return player_->get_battery_level();
}

/**
 * @brief Sets the heading angle of the homebase.
 * @param head_angle Heading angle in degrees
 */
void Arena::home_base_change_direction(double head_angle) {
	home_base_->set_heading_angle(head_angle);
}

/**
 * @brief Checks players battery level. Updates the players pause status, and
 * battery level for a single timestep
 * @param ec Pointer to a collision event.
 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
 */
int Arena::UpdatePlayerTimestep(EventCollision * const ec) {
	/*
	 * Check if the player has run out of battery
	 */
	if (player_->get_battery_level() <=0) {
		return 0;
	}

	/*
	 * If pause time is positive, the player is frozen and thus should not move
	 */
	if (player_->get_pause_time() > 0) {
		player_->set_speed(0);
		player_->set_pause_time(player_->get_pause_time() - 1);
	}

	/*
	 * Check if the player has collided with the recharge station. These
	 * need to be before the general collisions, which can move the
	 * robot away from these "obstacles" before the "collisions" have been
	 * properly processed.
	 */
	CheckForEntityCollision(player_, recharge_station_, &ec,
	                        player_->get_collision_delta(),
	                        player_->get_heading_angle());

	if (ec.collided()) {
		EventRecharge er;
		player_->Accept(&er);
	}

	return 2;
}

/**
 * @brief Update HomeBase heading angle for a single timestep
 */
void Arena::UpdateHomebaseTimestep(void) {
	// Randomly update homebase's heading angle
	int random_number1;
	random_number1 = rand() % 37;

	// If random number is one, change heading angle of homebase to random angle
	if (random_number1 == 1) {
		int random_heading;
		random_heading = rand() % 360;
		home_base_->set_heading_angle(random_heading);
	}
}

/**
 * @brief Checks if a robot has collided with HomeBase and switches them to a Superbot if so
 * @param ent The entity to check.
 * @param ec Pointer to a collision event.
 * @return int Boolean to show if HomeBase collision occured
 */
int Arena::CheckForRobotHomeBaseCollision(Robot * ent, EventCollision * const ec) {
	CheckForEntityCollision(ent, home_base_, &ec,
	                        ent->get_collision_delta(),
	                        ent->get_heading_angle());
	if ( ec.collided() ) {
		/*
		 * When robot collides with homebase, move robot out of gameplay arena
		 * and replace with a superbot at that location. Add superbot to
		 * entities_ and mobile_entities_ and remove the robot.
		 */
		superbot_entities_[n_superbots_]->set_pos(ent->get_pos());
		superbot_entities_[n_superbots_]->
		set_heading_angle(ent->get_heading_angle());
		superbot_entities_[n_superbots_]->set_speed(ent->get_speed());
		entities_.push_back(superbot_entities_[n_superbots_]);
		mobile_entities_.push_back(superbot_entities_[n_superbots_]);
		ent->set_pos(Position(1050, 860)); // move to off screen
		ent->set_super(1);
		entities_.erase(std::remove(entities_.begin(), entities_.end(), ent),
		                entities_.end());
		mobile_entities_.erase(std::remove(mobile_entities_.begin(),
		                                   mobile_entities_.end(), ent), mobile_entities_.end());
		n_superbots_++;
		break;
	}

	return ec.collided();
}

/**
 * @brief Checks if a robot has collided with player and freezes robot if so
 * @param ent The entity to check.
 * @param ec Pointer to a collision event.
 */
void Arena::CheckForRobotPlayerCollision(Robot * ent, EventCollision * const ec) {
	// When robot collides with player, robot freezes.
	CheckForEntityCollision(ent, player_, &ec,
	                        ent->get_collision_delta(),
	                        ent->get_heading_angle());
	if ( ec.collided() ) {
		ent->set_speed(0);
		ent->set_frozen(1);
	}
}

/**
 * @brief Checks if a robot has collided another robot and unfreezes robot if it is frozen
 * @param ent The entity to check.
 * @param ec Pointer to a collision event.
 */
void Arena::CheckForRobotRobotCollision(Robot * ent, EventCollision * const ec) {
	// Check for all other robot collisions
	if ( !ec.collided() ) {
		for (size_t i = 0; i < robot_entities_.size(); ++i) {
			if (robot_entities_[i] == ent) {
				continue;
			}
			CheckForEntityCollision(ent, robot_entities_[i], &ec,
			                        ent->get_collision_delta(),
			                        ent->get_heading_angle());
			if (ec.collided()) {
				robot_entities_[i]->set_frozen(0);
				robot_entities_[i]->set_speed(5);
				break;
			}
		}
	}
	ent->Accept(&ec);
}

/**
 * @brief Check for robot collisions
 * @param ec Pointer to a collision event.
 */
void Arena::UpdateRobotsTimestep(EventCollision * const ec) {
	// Check robot entities for collisions with various entities and
	// perform necessary functionality.
	for (auto ent : robot_entities_) {
		if (CheckForRobotHomeBaseCollision(ent, &ec)) {
			break;
		}

		CheckForRobotPlayerCollision(ent, &ec);
		CheckForRobotRobotCollision(ent, &ec);
	}
}

/**
 * @brief Checks if a superbot has collided a player and pauses player if so
 * @param ent The entity to check.
 * @param ec Pointer to a collision event.
 */
void Arena::CheckForSuperbotPlayerCollision(Robot * ent, EventCollision * const ec) {
	// Player collisions with superbots yield a frozen player.
	CheckForEntityCollision(ent, player_, &ec,
	                        ent->get_collision_delta(),
	                        ent->get_heading_angle());
	if ( ec.collided() ) {
		player_->set_pause_time(100);
		player_->set_speed(0);
	}
}

/**
 * @brief Check for superbot collisions
 * @param ec Pointer to a collision event.
 */
void Arena::UpdateSuperbotsTimestep(EventCollision * const ec) {
	// Next, check superbot entities for collisions with various entities and
	// perform necessary functionality.
	for (auto ent : superbot_entities_) {
		CheckForSuperbotPlayerCollision(ent, &ec);

		CheckForRobotRobotCollision(ent, &ec);
	}
}

/**
 * @brief Checks if robot or superbot is in proximity of another entity and trigger proximity event if so
 * @param rob Robot or Superbot
 * @param ent Entity that may be in proximity of Robot
 * @param ep Pointer to a proximity event
 * @param et Pointer to entity type event
 * @param ed Pointer to distress event
 * @param range Range between two entites to trigger proximity event
 */
void Arena::CheckForProximityEvent(const class Robot* const rob,
					   class ArenaEntity* ent, EventProximity * const ep,
						   EventEntityType * const et, EventDistress * const ed, double range) {

	CheckForWallInProximity(ent, &ep, &et, ent->get_proximity_range());
	if (!ep.activated()) {
		for (size_t i = 0; i < entities_.size(); ++i) {
			if (entities_[i] == ent) {
				continue;
			}
			CheckForEntityInProximity(ent, entities_[i], &ep, &et, &ed,
			                          ent->get_proximity_range());
			if (ep.activated()) {
				break;
			}
		}
	}
	ent->Accept(&ep);
	ent->Accept(&et);
}

/*
 * @brief Checks to see if all robots are frozen or collided with homebase.
 * If all are frozen or super, player wins. If all robots are super, player
 * loses.
 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
 */
int Arena::AllRobotsSuperOrFrozen(void) {
	int all_robots_frozen;
	all_robots_frozen = 1;
	int all_robots_super;
	all_robots_super = 1;
	for (auto ent : robot_entities_) {
		if ((!ent->get_frozen()) && (!ent->get_super())) {
			all_robots_frozen = 0;
		}
		if (!ent->get_super()) {
			all_robots_super = 0;
		}
	}

	if (all_robots_super)
		return 0; // player loses

	if (all_robots_frozen)
		return 1; // player wins

	return 2;
}

/**
 * @brief Update all entities for a single timestep
 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
 */
int Arena::UpdateEntitiesTimestep(void) {
	EventProximity ep;
	EventEntityType et;
	EventCollision ec;
	EventDistress ed;
	int game_status;

	// First, update the position of all entities, according to their current
	// velocities.
	for (auto ent : entities_) {
		ent->TimestepUpdate(1);
	}

	// Checks players battery level. Updates the players pause status, and battery level
	game_status = UpdatePlayerTimestep(&ec);
	if (game_status != 2) {
		return game_status;
	}

	UpdateHomebaseTimestep();
	UpdateRobotsTimestep(&ec);
	UpdateSuperbotsTimestep(&ec);

	/*
	 * Finally, some pairs of entities may now be close enough to be considered
	 * colliding, send collision events as necessary.
	 *
	 * When something collides with an immobile entity, the immobile entity does
	 * not move (duh), so no need to send it a collision event.
	 */
	for (auto ent : mobile_entities_) {
		// Check if entity is out of bounds. If so, use that as point of contact.
		CheckForEntityOutOfBounds(ent, &ec);

		// If not at wall, check if it is colliding with any other entities (not
		// itself)
		/**
		 * TODO: I believe this repeats some of the same collision checks as above,
		 * thus causing entities to "stick" to each other.
		 * Walls and immobile entites are not checked above. besides player/rechargestation
		 */
		if (!ec.collided()) {
			for (size_t i = 0; i < entities_.size(); ++i) {
				if (entities_[i] == ent) {
					continue;
				}
				CheckForEntityCollision(ent, entities_[i], &ec,
				                        ent->get_collision_delta(),
				                        ent->get_heading_angle());
				if (ec.collided()) {
					break;
				}
			}
		}
		ent->Accept(&ec);
	}

	/*
	 * Robots have a proximity sensor that allows them to move out
	 * of the way of incoming entities. This checks if robots are in proximity to
	 * any entities
	 */
	for (auto ent : robot_entities_) {
		CheckForProximityEvent(ent, entities_[i], &ep, &et, &ed,
		                       ent->get_proximity_range());
	}

	/*
	 * Superbots have a proximity sensor that allows them to move out
	 * of the way of incoming entities. This checks if superbots are in proximity to
	 * any entities
	 */
	for (auto ent : superbot_entities_) {
		CheckForProximityEvent(ent, entities_[i], &ep, &et, &ed,
		                       ent->get_proximity_range());
	}

	/*
	 * Checks to see if all robots are frozen or collided with homebase.
	 * If all are frozen or super, player wins. If all robots are super, player
	 * loses.
	 */
	game_status = AllRobotsSuperOrFrozen();
	return game_status;
}

/**
 * @brief Determine if a particular entity is gone out of the boundaries of
 * the simulation.
 * @param ent The entity to check.
 * @param event Pointer to a collision event.

 * Collision event is populated appropriately.
 */
void Arena::CheckForEntityOutOfBounds(ArenaMobileEntity * ent,
                                      EventCollision * const event) {
	double ent_x = ent->get_pos().x();
	double ent_y = ent->get_pos().y();
	// Angle of reflection should be 180-heading for walls
	// Right Wall
	if (ent->get_pos().x() + ent->get_radius() >= x_dim_) {
		event->collided(true);
		event->point_of_contact(Position(x_dim_, ent->get_pos().y()));
		event->angle_of_contact(-((360 - ent->get_heading_angle()) + 180));
		ent->set_pos(Position(ent_x - 10, ent_y));
	}
	else if (ent->get_pos().x() - ent->get_radius() <= 0) { // Left Wall
		event->collided(true);
		event->point_of_contact(Position(0, ent->get_pos().y()));
		event->angle_of_contact(-((360 - ent->get_heading_angle()) + 180));
		ent->set_pos(Position(ent_x + 10, ent_y));
	}
	else if (ent->get_pos().y() + ent->get_radius() >= y_dim_) { // Bottom Wall
		event->collided(true);
		event->point_of_contact(Position(ent->get_pos().x(), y_dim_));
		event->angle_of_contact(ent->get_heading_angle());
		ent->set_pos(Position(ent_x, ent_y - 10));
	}
	else if (ent->get_pos().y() - ent->get_radius() <= 0) { // Top Wall
		event->collided(true);
		event->point_of_contact(Position(0, y_dim_));
		event->angle_of_contact(ent->get_heading_angle());
		ent->set_pos(Position(ent_x, ent_y + 10));
	}
	else {
		event->collided(false);
	}
}

/**
 * @brief Determine if two entities have collided in the arena. Collision is
 * defined as the difference between the extents of the two entities being less
 * than a run-time parameter.
 *
 * @param ent1 Entity #1.
 * @param ent2 Entity #2.
 * @param event Pointer to a collision event
 * @param collision_delta Buffer for collisions
 * @param h_angle The heading angle of entity #1
 *
 * Collision Event is populated appropriately.
 */
void Arena::CheckForEntityCollision(const ArenaEntity* const ent1,
                                    const ArenaEntity* const ent2, EventCollision * const event,
                                    double collision_delta, double h_angle) {
	/* Note: this assumes circular entities */
	double ent1_x = ent1->get_pos().x();
	double ent1_y = ent1->get_pos().y();
	double ent2_x = ent2->get_pos().x();
	double ent2_y = ent2->get_pos().y();
	double dist = std::sqrt(std::pow(ent2_x - ent1_x, 2) +
	                        std::pow(ent2_y - ent1_y, 2));
	if (dist > ent1->get_radius() + ent2->get_radius() + collision_delta) {
		event->collided(0);
	}
	else {
		// Populate the collision event.
		// Collided is true
		// Point of contact is point along perimeter of ent1
		// Angle of contact is angle to that point of contact
		// TODO: fix collision logic.
		double adj = ent2_x - ent1_x;
		double opp = ent2_y - ent1_y;
		double angle = atan(opp / adj) * (180/3.14159265);
		double bounce_angle = angle + 90;
		double adjusted_angle = (180 - bounce_angle) + (h_angle - 180);
		double new_head = bounce_angle - adjusted_angle;

		event->angle_of_contact(-new_head);
		event->collided(1);
	}
}

/**
 * @brief Determine if two entities are in proximity of one another.
 * Proximity is defined as the if the entities are closer than the range
 * number in the proximity sensor.
 *
 * @param rob Robot or Superbot
 * @param ent Entity that may be in proximity of Robot
 * @param ep Pointer to a proximity event
 * @param et Pointer to entity type event
 * @param ed Pointer to distress event
 * @param range Range between two entites to trigger proximity event
 *
 * Proximity Event is populated appropriately.
 */
void Arena::CheckForEntityInProximity(const class Robot* const rob,
					      class ArenaEntity* ent, EventProximity * const ep,
						      EventEntityType * const et, EventDistress * const ed, double range) {
	double rob_x = rob->get_pos().x();
	double rob_y = rob->get_pos().y();
	double ent_x = ent->get_pos().x();
	double ent_y = ent->get_pos().y();
	double dist = std::sqrt(std::pow(ent_x - rob_x, 2) +
	                        std::pow(ent_y - rob_y, 2));
	if (dist > rob->get_radius() + ent->get_radius() + range) {
		ep->activated(0);
	}
	else {
		if (ent->get_name() == "Robot") {
			Robot* rob2 = dynamic_cast<Robot*>(ent);
			if (!rob2->get_frozen()) { // If robot not frozen avoid
				ep->angle_of_contact(rob->get_heading_angle());
				ep->activated(1);
				et->activated(kRobot);
			}
			else { // if robot frozen continue heading
				ed->collided(1);
				ep->activated(0);
			}
		}
		else if ((ent->get_name() == "Home Base") && (rob->get_name() == "Robot")) { // continue heading
			ep->activated(0);
			et->activated(kHomebase);
		}
		// TODO: Make sure when rob is superbot rob->get_name() == "Superbot"
		else if ((ent->get_name() == "Player") && (rob->get_name() == "Superbot")) { // continue heading
			ep->activated(0);
			et->activated(kPlayer);
		}
		else { // avoid
			ep->angle_of_contact(rob->get_heading_angle());
			ep->activated(1);
		}
	}
}

/**
 * @brief Determine if a particular robot is in proximity of the boundaries
 * of the simulation.
 *
 * @param ent The Robot to check.
 * @param event Pointer to a proximity event.
 * @param et Emits the type of entity the robot is in proximity of
 * @param range Range in which event will trigger if entity is within
 *
 * Proximity event is populated appropriately.
 */
void Arena::CheckForWallInProximity(class Robot* ent,
					    EventProximity * const event, EventEntityType * const et, double range) {
	double ent_x = ent->get_pos().x();
	double ent_y = ent->get_pos().y();
	if (ent->get_pos().x() + ent->get_radius() + range >= x_dim_) { // Right
		event->activated(true);
		et->activated(kWall);
		event->point_of_contact(Position(x_dim_, ent->get_pos().y()));
		event->angle_of_contact(-((360 - ent->get_heading_angle()) + 180));
		ent->set_pos(Position(ent_x, ent_y));
	}
	else if (ent->get_pos().x() - ent->get_radius() - range <= 0) { // Left
		event->activated(true);
		et->activated(kWall);
		event->point_of_contact(Position(0, ent->get_pos().y()));
		event->angle_of_contact(-((360 - ent->get_heading_angle()) + 180));
		ent->set_pos(Position(ent_x, ent_y));
	}
	else if (ent->get_pos().y() + ent->get_radius() + range >= y_dim_) {
		event->activated(true);
		et->activated(kWall);
		event->point_of_contact(Position(ent->get_pos().x(), y_dim_));
		event->angle_of_contact(ent->get_heading_angle());
		ent->set_pos(Position(ent_x, ent_y));
	}
	else if (ent->get_pos().y() - ent->get_radius() - range <= 0) { // Top
		event->activated(true);
		et->activated(kWall);
		event->point_of_contact(Position(0, y_dim_));
		event->angle_of_contact(ent->get_heading_angle());
		ent->set_pos(Position(ent_x, ent_y));
	}
	else {
		event->activated(false);
	}
}

/**
 * @brief Handle the key press passed along by the viewer.
 * @param key Value of a key press
 */
void Arena::Accept(int key) {
	EventKeypress e(key);
	EventCommand ec(e.keypress_to_cmd(key));
	player_->EventCmd(ec.cmd());
}

NAMESPACE_END(csci3081);
