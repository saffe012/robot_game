/**
 * @file motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_MOTION_HANDLER_H_
#define SRC_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"
#include "src/robot_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The handler for the entity's actuators, which in this case are the two
 * wheel actuators. Its main job is to translate the directional commands from
 * the user into the appropriate differential drive wheel speeds.
 *
 * Manages the modification to the velocity based on user input and
 * collisions. \ref MotionBehavior translates velocity and position to a
 * new position.  Both of these are straightforward, but the framework allows
 * for more sophisticated models of motion in which each wheel has distinct
 * speed.
 *
 * For this iteration, both wheels are always going at maximum speed, and
 * cannot be controlled independently.
 */
class MotionHandler {
public:
	/**
	 * @brief MotionHandler constructor
	 */
	MotionHandler(void) : heading_angle_(0),
		speed_(0), max_speed_(15) {
	}

	/**
	 * @brief Reset the actuators to their newly constructed/un-commanded state.
	 */
	void Reset(void);

	/**
	 * @brief Change the speed and direction according to the sensor readings.
	 * @param touch sensor that can be activated and contains point-of-contact.
	 */
	void UpdateVelocity(SensorTouch st);

	/**
	 * @brief Gets the speed of an entity
	 * @return double The speed of the entity
	 */
	double get_speed(void) const {
		return speed_;
	}

	/**
	 * @brief Sets the speed of an entity
	 * @param sp The speed of the entity
	 */
	void set_speed(double sp) {
		speed_ = sp;
	}

	/**
	 * @brief Gets the direction of travel of the entity
	 * @return double The direction of travel of the entity
	 */
	double get_heading_angle(void) const {
		return heading_angle_;
	}

	/**
	 * @brief Sets the direction of travel of the entity
	 * @param ha The direction of travel of the entity
	 */
	void set_heading_angle(double ha) {
		heading_angle_ = ha;
	}

	/**
	 * @brief Gets the max speed of an entity
	 * @return double The max speed of the entity
	 */
	double get_max_speed(void) const {
		return max_speed_;
	}

	/**
	 * @brief Sets the max speed of an entity
	 * @param ms The max speed of the entity
	 */
	void set_max_speed(double ms) {
		max_speed_ = ms;
	}

private:
	double heading_angle_; // The direction of travel of the entity
	double speed_; // The speed of the entity
	double max_speed_; // The max speed of the entity
};

NAMESPACE_END(csci3081);

#endif  // SRC_MOTION_HANDLER_H_
