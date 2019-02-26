/**
 * @file superbot_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPERBOT_MOTION_HANDLER_H_
#define SRC_SUPERBOT_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/superbot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/motion_handler.h"
#include "src/sensor_proximity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the robot's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * Manages the modification to the velocity based on user input and
 * collisions. \ref RobotMotionBehavior translates velocity and position to a
 * new position.  Both of these are straightforward, but the framework allows
 * for more sophisticated models of motion in which each wheel has distinct
 * speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */

class MotionHandlerSuperBot : public MotionHandler {
 public:
  MotionHandlerSuperBot(void);

  /**
   * @brief Reset the actuators to their newly constructed/un-commanded state.
   */
  void Reset(void);

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param touch sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorTouch st);

  /**
  * @brief Change the speed and direction according to the sensor readings.
  *
  * @param proximity sensor that can be activated and contains point-of-contact.
  *
  */
  void UpdateVelocity(SensorProximity sp);

  double get_speed(void) const { return speed_; }
  void set_speed(double sp) { speed_ = sp; }

  double get_heading_angle(void) const { return heading_angle_;}
  void set_heading_angle(double ha) { heading_angle_ = ha; }

  double get_max_speed(void) const { return max_speed_; }
  void set_max_speed(double ms) { max_speed_ = ms; }

 private:
  double heading_angle_;
  double speed_;
  double max_speed_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SUPERBOT_MOTION_HANDLER_H_
