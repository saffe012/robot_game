/**
 * @file player.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_H_
#define SRC_PLAYER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/player_motion_handler.h"
#include "src/player_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/player_battery.h"
#include "src/arena_mobile_entity.h"
#include "src/event_recharge.h"
#include "src/event_entity_type.h"
#include "src/event_collision.h"
#include "src/event_proximity.h"
#include "src/event_distress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile robot within the arena.
 *
 * Robots have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Player : public ArenaMobileEntity {
 public:
  explicit Player(const struct player_params* const params);

  /**
   * @brief Reset the player's battery to full after an encounter with the
   * recharge station.
   */
  void ResetBattery(void);

  /**
   * @brief Reset the player to a newly constructed state (needed for reset
   * button to work in arena GUI).
   */
  void Reset(void) override;

  /**
   * @brief Update the player's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief Accept a recharge event.
   *
   * This causes the player's battery to become fully charged.
   *
   * @param e The recharge event.
   */
  void Accept(const EventRecharge * const e);

  /**
   * @brief  Pass along a collision event (from arena) to the touch sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The player's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) override;

  /**
   * @brief  Pass along a proximity event (from arena) to the proximity sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The player's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The proximity event.
   */
  void Accept(const EventProximity * const e);

  /**
   * @brief  Pass along a distress event (from arena) to the distress sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The player's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The distress event.
   */
  void Accept(const EventDistress * const e);


  /**
   * @brief  Pass along an entity type event (from arena) to the entity type sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The player's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The entity type event.
   */
  void Accept(const EventEntityType * const e);

  /**
   * @brief Handle user input commands to change the heading or speed.
   *
   * @param cmd The command to process.
   */
  void EventCmd(enum event_commands cmd);

  /**
   * @brief Get the current battery level of the player.
   */
  double get_battery_level(void) { return battery_.level(); }

  // getters and setters

  double get_heading_angle(void) const override {
    return motion_handler_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_.set_heading_angle(ha);
  }
  double get_speed(void) const override { return motion_handler_.get_speed(); }
  void set_speed(double sp) override { motion_handler_.set_speed(sp); }

  std::string get_name(void) const override {
    return "Player";
  }

  int get_pause_time(void) { return pause_time_; }
  void set_pause_time(int pause) { pause_time_ = pause; }

 private:
  static unsigned int next_id_;

  int id_;
  int pause_time_;  // pause time for when superbot collides with player
  double heading_angle_;
  double angle_delta_;
  PlayerBattery battery_;
  MotionHandlerPlayer motion_handler_;
  PlayerMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_H_
