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
	/**
	 * @brief MotionHandlerSuperBot constructor
	 */
	MotionHandlerSuperBot(void);

	/**
 * @brief Reset the actuators to their newly constructed/un-commanded state.
 */
	void Reset(void);

	/**
	 * @brief Change the speed and direction according to the sensor readings.
	 * @param st Touch sensor that can be activated and contains point-of-contact.
	 */
	void UpdateVelocity(SensorTouch st);

	/**
	 * @brief Change the speed and direction according to the sensor readings.
	 * @param sp Proximity sensor that can be activated and contains point-of-contact.
	 */
	void UpdateVelocity(SensorProximity sp);


	/**
	 * @brief Gets the speed of the robot
	 * @return double Speed of the robot
	 */
	double get_speed(void) const {
		return speed_;
	}

	/**
	 * @brief Sets the speed of the robot
	 * @param sp Speed of the robot
	 */
	void set_speed(double sp) {
		speed_ = sp;
	}

	/**
	 * @brief Gets the heading angle of the robot
	 * @return double Angle in degrees the robot is travelling
	 */
	double get_heading_angle(void) const {
		return heading_angle_;
	}

	/**
	 * @brief Sets the heading angle of the robot
	 * @param ha Angle in degrees the robot is travelling
	 */
	void set_heading_angle(double ha) {
		heading_angle_ = ha;
	}

	/**
	 * @brief Gets the max speed of the player
	 * @return double highest speed possible for player
	 */
	double get_max_speed(void) const {
		return max_speed_;
	}

	/**
	 * @brief Sets the max speed of the player
	 * @param ms highest speed possible for player
	 */
	void set_max_speed(double ms) {
		max_speed_ = ms;
	}

private:
	double heading_angle_; // angle in degrees the robot is travelling
	double speed_; // speed the robot is travelling
	double max_speed_; // highest speed possible for robot
};

NAMESPACE_END(csci3081);

#endif  // SRC_SUPERBOT_MOTION_HANDLER_H_
