/**
 * @file player_motion_handler.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_MOTION_HANDLER_H_
#define SRC_PLAYER_MOTION_HANDLER_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_commands.h"

#include "src/player_params.h"
#include "src/arena_mobile_entity.h"
#include "src/sensor_touch.h"
#include "src/sensor_proximity.h"
#include "src/motion_handler.h"

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

class MotionHandlerPlayer : public MotionHandler {
public:
	/**
	 * @brief MotionHandlerPlayer constructor
	 */
	MotionHandlerPlayer(void);

	/**
	 * @brief Reset the actuators to their newly constructed/un-commanded state.
	 */
	void Reset(void);

	/**
	 * @brief Command from user keypress via the viewer.
	 * @param cmd The command.
	 */
	void AcceptCommand(enum event_commands cmd);

	/**
	 * @brief Change the speed and direction according to the sensor readings.
	 * @param st Touch sensor that can be activated and contains point-of-contact.
	 */
	void UpdateVelocity(SensorTouch st);

	/**
	 * @brief Gets the speed of the player
	 * @return double Speed of the player
	 */
	double get_speed(void) const {
		return speed_;
	}

	/**
	 * @brief Sets the speed of the player
	 * @param sp Speed of the player
	 */
	void set_speed(double sp) {
		speed_ = sp;
	}

	/**
	 * @brief Gets the heading angle of the player
	 * @return double Angle in degrees the player is travelling
	 */
	double get_heading_angle(void) const {
		return heading_angle_;
	}

	/**
	 * @brief Sets the heading angle of the player
	 * @param ha Angle in degrees the player is travelling
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
	double heading_angle_; // angle in degrees the player is travelling
	double speed_; // speed the player is travelling
	double max_speed_; // highest speed possible for player
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_MOTION_HANDLER_H_
