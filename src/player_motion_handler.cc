/**
 * @file player_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/player_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
/**
 * @brief MotionHandlerPlayer constructor
 */
MotionHandlerPlayer::MotionHandlerPlayer() :
	heading_angle_(0),
	speed_(0),
	max_speed_(15) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Command from user keypress via the viewer.
 * @param cmd The command.
 */
void MotionHandlerPlayer::AcceptCommand(enum event_commands cmd) {
	switch (cmd) {
	case COM_TURN_LEFT:
		set_heading_angle(heading_angle_ - 10);
		if (heading_angle_ < 0) {
			heading_angle_ += 360;
		}
		break;
	case COM_TURN_RIGHT:
		set_heading_angle(heading_angle_ + 10);
		if (heading_angle_ >= 360) {
			heading_angle_ -= 360;
		}
		break;
	case COM_SPEED_UP:
		if (speed_ < max_speed_) {
			set_speed(speed_ + 1);
		}
		break;
	case COM_SLOW_DOWN:
		if (speed_ > 0) {
			set_speed(speed_ - 1);
		}
		break;
	default:
		std::cerr << "FATAL: bad actuator command" << std::endl;
		assert(0);
	}
}

/**
 * @brief Change the speed and direction according to the sensor readings.
 * @param st Touch sensor that can be activated and contains point-of-contact.
 */
void MotionHandlerPlayer::UpdateVelocity(SensorTouch st) {
	// std::cout << "Heading angle: " << heading_angle_ << std::endl;
	if (st.activated()) {
		heading_angle_ = -st.angle_of_contact();
		if (heading_angle_ < 0) {
			heading_angle_ += 360;
		}
	}
}

/**
 * @brief Reset the actuators to their newly constructed/un-commanded state.
 */
void MotionHandlerPlayer::Reset() {
	heading_angle_ = get_heading_angle();
	speed_ = 5;
}

NAMESPACE_END(csci3081);
