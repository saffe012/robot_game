/**
 * @file robot_battery.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_BATTERY_H_
#define SRC_PLAYER_BATTERY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"
#include "src/event_collision.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
/**
 * @brief The battery for a robot.
 */
class PlayerBattery {
public:
	/**
	 * @brief PlayerBattery constructor
	 * @param max_charge The maximum and starting charge level for the battery
	 */
	explicit PlayerBattery(double max_charge) : charge_(max_charge),
		max_charge_(max_charge) {
	}

	/**
	 * @brief The amount of energy consumed by the player due to its linear speed
	 * its is directly proportional to that speed, with a scaling factor.
	 */
	double kLINEAR_SCALE_FACTOR = 0.01;

	/**
	 * @brief The amount of energy consumed by the player due to its angular speed
	 * its is directly proportional to that speed, with a scaling factor.
	 */
	double kANGULAR_SCALE_FACTOR = 0.01;

	/**
	 * @brief Get the current battery level.
	 * @return double Battery level of robot
	 */
	double level(void) const {
		return charge_;
	}

	/**
	 * @brief Handle a recharge event by instantly restoring the player's battery
	 * to its maximum value.
	 */
	void EventRecharge(void) {
		charge_ = max_charge_ + 5;
	}

	/**
	 * @brief Reset the player's battery to its newly constructed/undepleted state.
	 */
	void Reset(void) {
		charge_ = max_charge_;
	}

	/**
	 * @brief Calculate the new battery level based on the distance travelled
	 * @param old_pos Entities Position at last simulation update
	 * @param new_pos Entities Position at current simulation update
	 * @param dt Change in time of simulation
	 * @return double The updated battery level.
	 */
	double Deplete(Position old_pos,
	               Position new_pos, __unused double dt);

	/**
 * @brief This is how the battery can be informed a collision occured.
 * Deplete accordingly.
 * @param a collision event.
 */
	void Accept(const EventCollision * const e);

private:
	double charge_; // current battery level of robot
	double max_charge_; // highest possible battery level of robot
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_BATTERY_H_
