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
   */
  int AdvanceTime(void);

  /**
  * @brief Handle the key press passed along by the viewer.
  *
  * @param[in] an event holding the key press.
  *
  */
  // void Accept(const EventKeypress * const e);
  void Accept(int key);

  /**
   * @brief Reset all entities in the arena, effectively restarting the game.
   */
  void Reset(void);

  /**
   * @brief Get the # of players in the arena.
   */
  unsigned int n_players(void) { return n_players_; }

  /**
   * @brief Get # of obstacles in the arena.
   */
  unsigned int n_obstacles(void) { return n_obstacles_; }


  /**
   * @brief Returns the level of the player battery.
   */
  double get_player_battery_level(void);

  /**
   * @brief Sets the heading angle of the homebase.
   *
   * @param[in] a heading angle.
   *
   */
  void home_base_change_direction(double head_angle);

  /**
   * @brief Get a list of all obstacles (i.e. non-mobile entities in the arena).
   */
  std::vector<class Obstacle*> obstacles(void);


  /**
   * @brief Get a list of all robots.
   */
  std::vector<class Robot*> robots(void);

  /**
   * @brief Get a list of all Superbots.
   */
  std::vector<class SuperBot*> superbots(void);

  /**
   * @brief Get the list of all mobile entities in the arena.
   */
  std::vector<class ArenaMobileEntity*> mobile_entities(void)
    { return mobile_entities_; }

  /**
   * @brief Get the RechargeStation object in the Arena.
   */
  class RechargeStation* recharge_station(void) const {
    return recharge_station_;
  }

  /**
   * @brief Get the Player object in the Arena.
   */
  class Player* player(void) const { return player_; }

  /**
   * @brief Get the HomeBase object in the Arena.
   */
  class HomeBase* home_base(void) const { return home_base_; }

 private:
  /**
   * @brief Determine if any entities in the arena are overlapping.
   *
   * @return TRUE if any entities overlap, FALSE if no entities overlap.
   */
  bool any_entities_overlap(void);

  /**
   * @brief Determine if two entities have collided in the arena. Collision is
   * defined as the difference between the extents of the two entities being less
   * than a run-time parameter.
   *
   * @param ent1 Entity #1.
   * @param ent2 Entity #2.
   * @param pointer to a collision event
   * @param the collision_delta
   * @para, the heading angle of entity #1
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
   * @param pointer to a collision event.
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
   * @param rob Robot.
   * @param ent2 Entity #2.
   * @param pointer to a proximity event
   * @param pointer to entity type event
   * @param pointer to distress event
   * @param proximity range
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
   * @param rob SuperBot.
   * @param ent2 Entity #2.
   * @param pointer to a proximity event
   * @param pointer to entity type event
   * @param pointer to distress event
   * @param proximity range
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
   * @param pointer to a proximity event.
   * @param entity type event
   * @param proximity range
   *
   * Proximity event is populated appropriately.
   */
  void CheckForWallInProximity(class Robot* ent,
    EventProximity * const ep, EventEntityType * const et, double range);

  /**
   * @brief Update all entities for a single timestep
   */
  int UpdateEntitiesTimestep(void);

  // Under certain circumstance, the compiler requires that the copy
  // constructor is not defined. This is deleting the default copy const.
  Arena& operator=(const Arena& other) = delete;
  Arena(const Arena& other) = delete;

  // Dimensions of graphics window inside which robots must operate
  double x_dim_;
  double y_dim_;
  unsigned int n_players_;
  unsigned int n_obstacles_;
  unsigned int n_robots_;
  unsigned int n_superbots_;

  // Entities populating the arena
  Player* player_;
  RechargeStation * recharge_station_;
  HomeBase * home_base_;
  std::vector<class ArenaEntity*> entities_;
  std::vector<class ArenaMobileEntity*> mobile_entities_;
  std::vector<class Robot*> robot_entities_;
  std::vector<class SuperBot*> superbot_entities_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_H_
