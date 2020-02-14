/**
 * @file robot_arena.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_H_
#define SRC_ARENA_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include "src/event_keypress.h"
#include "src/event_collision.h"
#include "src/player.h"
#include "src/superbot.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
struct arena_params;

/**
 * @brief The main class for the simulation of a 2D world with many robots running
 * around.
 *
 * \ref GraphicsArenaViewer or Tests call \ref AdvanceTime to control the
 * simulation and use the get*() functions to read out the current state of the
 * simulation (i.e., the current positions and orientations of player, robots and
 * obstacles).
 */
class Arena {
public:
	explicit Arena(const struct arena_params * const params);
	~Arena(void);

	/**
	 * @brief Advance the simulation by the specified # of steps.
	 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
	 */
	int AdvanceTime(void);

	/**
	 * @brief Handle the key press passed along by the viewer.
	 * @param key Value of a key press
	 */
	void Accept(int key);

	/**
	 * @brief Reset all entities in the arena, effectively restarting the game.
	 */
	void Reset(void);

	/**
	 * @brief Get the # of players in the arena.
	 * @return unsigned int Number of players in Arena
	 */
	unsigned int n_players(void) {
		return n_players_;
	}

	/**
	 * @brief Get # of obstacles in the arena.
	 * @return unsigned int Number of obstacles in the Arena
	 */
	unsigned int n_obstacles(void) {
		return n_obstacles_;
	}


	/**
	 * @brief Returns the level of the player battery.
	 * @return double Player's battery level
	 */
	double get_player_battery_level(void);

	/**
	 * @brief Sets the heading angle of the homebase.
	 * @param head_angle Heading angle in degrees
	 *
	 */
	void home_base_change_direction(double head_angle);

	/**
	 * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
	 * @return std::vector<Obstacle*> A vector containing the obstacles in the arena
	 */
	std::vector<class Obstacle*> obstacles(void);


	/**
	 * @brief Get a list of all robots.
	 * @return std::vector<Robot*> A vector containing the Robots in the arena
	 */
	std::vector<class Robot*> robots(void);

	/**
	 * @brief Get a list of all Superbots.
	 * @return std::vector<SuperBot*> A vector containing the Superbots in the arena
	 */
	std::vector<class SuperBot*> superbots(void);

	/**
	 * @brief Get the list of all mobile entities in the arena.
	 * @return std::vector<ArenaMobileEntity*> A vector containing the mobile entites in the arena
	 */
	std::vector<class ArenaMobileEntity*> mobile_entities(void)
	{
		return mobile_entities_;
	}

	/**
	 * @brief Get the RechargeStation object in the Arena.
	 * @return RechargeStation* The RechargeStation in the arena
	 */
	class RechargeStation* recharge_station(void) const {
		return recharge_station_;
	}

	/**
	 * @brief Get the Player object in the Arena.
	 * @return Player* The Player in the arena
	 */
	class Player* player(void) const {
		return player_;
	}

	/**
	 * @brief Get the HomeBase object in the Arena.
	 * @return HomeBase* The HomeBase in the arena
	 */
	class HomeBase* home_base(void) const {
		return home_base_;
	}

private:
	/**
	 * @brief Checks players battery level. Updates the players pause status, and
	 * battery level for a single timestep
	 * @param ec Pointer to a collision event.
	 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
	 */
	int UpdatePlayerTimestep(EventCollision * const ec);

	/**
	 * @brief Update HomeBase heading angle for a single timestep
	 */
	void UpdateHomebaseTimestep(void);

	/**
	 * @brief Checks if a robot has collided with HomeBase and switches them to a Superbot if so
	 * @param ent The entity to check.
	 * @param ec Pointer to a collision event.
	 * @return int Boolean to show if HomeBase collision occured
	 */
	int CheckForRobotHomeBaseCollision(Robot * ent, EventCollision * const ec);

	/**
	 * @brief Checks if a robot has collided with player and freezes robot if so
	 * @param ent The entity to check.
	 * @param ec Pointer to a collision event.
	 */
	void CheckForRobotPlayerCollision(Robot * ent, EventCollision * const ec);

	/**
	 * @brief Checks if a robot has collided another robot and unfreezes robot if it is frozen
	 * @param ent The entity to check.
	 * @param ec Pointer to a collision event.
	 */
	void CheckForRobotRobotCollision(Robot * ent, EventCollision * const ec);

	/**
	 * @brief Check for robot collisions
	 * @param ec Pointer to a collision event.
	 */
	void UpdateRobotsTimestep(EventCollision * const ec);

	/**
	 * @brief Checks if a superbot has collided a player and pauses player if so
	 * @param ent The entity to check.
	 * @param ec Pointer to a collision event.
	 */
	void CheckForSuperbotPlayerCollision(Robot * ent, EventCollision * const ec);

	/**
	 * @brief Check for superbot collisions
	 * @param ec Pointer to a collision event.
	 */
	void UpdateSuperbotsTimestep(EventCollision * const ec);

	/**
	 * @brief Checks if robot or superbot is in proximity of another entity and trigger proximity event if so
	 * @param rob Robot or Superbot
	 * @param ent Entity that may be in proximity of Robot
	 * @param ep Pointer to a proximity event
	 * @param et Pointer to entity type event
	 * @param ed Pointer to distress event
	 * @param range Range between two entites to trigger proximity event
	 */
	void CheckForProximityEvent(const class Robot* const rob,
					    class ArenaEntity* ent, EventProximity * const ep,
						    EventEntityType * const et, EventDistress * const ed, double range);

	/*
	 * @brief Checks to see if all robots are frozen or collided with homebase.
	 * If all are frozen or super, player wins. If all robots are super, player
	 * loses.
	 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
	 */
	int AllRobotsSuperOrFrozen(void);

	/**
	 * @brief Check for superbot collisions
	 * @param ec Pointer to a collision event.
	 */
	void UpdateSuperbotsTimestep(EventCollision * const ec);

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
	void CheckForEntityCollision(const class ArenaEntity* const ent1,
					     const class ArenaEntity* const ent2,
						     EventCollision * const ec,
						     double collision_delta, double h_angle);

	/**
	 * @brief Determine if a particular entity is gone out of the boundaries of
	 * the simulation.
	 *
	 * @param ent The entity to check.
	 * @param event Pointer to a collision event.
	 *
	 * Collision event is populated appropriately.
	 */
	void CheckForEntityOutOfBounds(class ArenaMobileEntity* ent,
					       EventCollision * const ec);

	/**
	 * @brief Determine if two entities are in proximity of one another.
	 * Proximity is defined as the if the entities are closer than the range
	 * number in the proximity sensor.
	 *
	 * @param rob Robot
	 * @param ent Entity that may be in proximity of Robot
	 * @param ep Pointer to a proximity event
	 * @param et Pointer to entity type event
	 * @param ed Pointer to distress event
	 * @param range Range between two entites to trigger proximity event
	 *
	 * Proximity Event is populated appropriately.
	 */
	void CheckForEntityInProximity(const class Robot* const rob,
					       class ArenaEntity* ent,
						       EventProximity * const ep,
						       EventEntityType * const et,
						       EventDistress * const ed,
						       double range);

	/**
	 * @brief Determine if a suberbot is in proximity of another entity.
	 * Proximity is defined as the if the entities are closer than the range
	 * number in the proximity sensor.
	 *
	 * @param rob Superbot
	 * @param ent Entity that may be in proximity of Superbot
	 * @param ep Pointer to a proximity event
	 * @param et Pointer to entity type event
	 * @param ed Pointer to distress event
	 * @param range Range between two entites to trigger proximity event
	 *
	 * Proximity Event is populated appropriately.
	 */
	void SuperBotCheckForEntityInProximity(const class SuperBot* const rob,
						       class ArenaEntity* ent,
							       EventProximity * const ep,
							       EventEntityType * const et,
							       EventDistress * const ed, double range);


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
	void CheckForWallInProximity(class Robot* ent,
					     EventProximity * const ep, EventEntityType * const et, double range);

	/**
	 * @brief Update all entities for a single timestep
	 * @return int Status of the game (0 = player loses, 1 = player wins, 2 = continue game)
	 */
	int UpdateEntitiesTimestep(void);

	/**
	 * Under certain circumstance, the compiler requires that the copy
	 * constructor is not defined. This is deleting the default copy const.
	 */
	Arena& operator=(const Arena& other) = delete;
	Arena(const Arena& other) = delete;

	// Dimensions of graphics window inside which robots must operate
	double x_dim_; // width
	double y_dim_; // height

	unsigned int n_players_; // Number of players in the Arena
	unsigned int n_obstacles_; // Number of obstacles in the Arena
	unsigned int n_robots_; // Number of robots in the Arena
	unsigned int n_superbots_; // Number of superbots in the Arena

	// Entities populating the arena
	Player* player_; // user controlled player
	RechargeStation * recharge_station_; // Player recharge station
	HomeBase * home_base_; // robot's home base
	std::vector<class ArenaEntity*> entities_; // Vector containing all entities in the arena
	std::vector<class ArenaMobileEntity*> mobile_entities_; // Vector containing all moving entities in the arena
	std::vector<class Robot*> robot_entities_; // Vector containing all robots in the arena
	std::vector<class SuperBot*> superbot_entities_; // Vector containing all superbots in the arena
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
