/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/event_entity_type.h"
#include "src/event_collision.h"
#include "src/event_proximity.h"
#include "src/event_distress.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"

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
class Robot : public ArenaMobileEntity {
 public:
  explicit Robot(const struct robot_params* const params);
  ~Robot(void);

  /**
   * @brief Reset the robot to a newly constructed state (needed for reset
   * button to work in arena GUI).
   */
  void Reset(void) override;

  /**
   * @brief Update the robot's position and velocity after the specified
   * duration has passed.
   *
   * @param dt The # of timesteps that have elapsed since the last update.
   */
  void TimestepUpdate(unsigned int dt) override;

  /**
   * @brief  Pass along a collision event (from arena) to the touch sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) override;

  /**
   * @brief  Pass along a proximity event (from arena) to the proximity sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The proximity event.
   */
  void Accept(const EventProximity * const e);

  /**
   * @brief  Pass along a distress event (from arena) to the distress sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The distress event.
   */
  void Accept(const EventDistress * const e);


  /**
   * @brief  Pass along an entity type event (from arena) to the entity type sensor.
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The robot's heading will be updated
   * to move it away from the incident angle at the point of contact.
   *
   * @param e The entity type event.
   */
  void Accept(const EventEntityType * const e);

  // getters and setters
  /**
   * @brief Gets the range of the proximity sensor
   */
  double get_proximity_range(void) {
    return sensor_proximity_1_.range();
  }

  double get_heading_angle(void) const override {
    return motion_handler_.get_heading_angle();
  }
  void set_heading_angle(double ha) override {
    motion_handler_.set_heading_angle(ha);
  }
  double get_speed(void) const override { return motion_handler_.get_speed(); }
  void set_speed(double sp) override { motion_handler_.set_speed(sp); }

  void set_frozen(int froze) { frozen_ = froze; }
  int get_frozen(void) { return frozen_; }

  void set_super(int super) { super_ = super; }
  int get_super(void) { return super_; }

  std::string get_name(void) const override {
    return "Robot";
  }

 private:
  static unsigned int next_id_;
  int frozen_;  // boolean to show whether robot is frozen or not
  int super_;  // boolean to show if robot has been collided with by home base
  int id_;
  double heading_angle_;
  double angle_delta_;
  Position starting_pos_;
  Position old_pos_;
  MotionHandlerRobot motion_handler_;
  RobotMotionBehavior motion_behavior_;
  SensorTouch sensor_touch_;
  SensorProximity sensor_proximity_1_;
  SensorProximity sensor_proximity_2_;
  SensorDistress sensor_distress_;
  SensorEntityType sensor_entity_type_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
