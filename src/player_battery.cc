/**
 * @file robot_battery.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <cmath>
#include <iostream>
#include "src/player_battery.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Calculate the new battery level based on the distance travelled
 * @param old_pos Entities Position at last simulation update
 * @param new_pos Entities Position at current simulation update
 * @param dt Change in time of simulation
 * @return double The updated battery level.
 */
double PlayerBattery::Deplete(Position old_pos,
                              Position new_pos, __unused double dt) {
	double ys, xs;

	xs = pow(old_pos.x() - new_pos.x(), 2);
	ys = pow(old_pos.y() - new_pos.y(), 2);

	int distance;

	distance = pow((xs + ys), .5);

	charge_ = charge_ - (distance * .01);

	if (charge_ < 0)
		charge_ = 0;

	return charge_;
}

/**
 * @brief This is how the battery can be informed a collision occured.
 * Deplete accordingly.
 * @param a collision event.
 */
void PlayerBattery::Accept(__unused const EventCollision * const e) {
	if (e->collided()) {
		charge_ -= 5;
	}
	if (charge_ < 0)
		charge_ = 0;

	// std::cout << "******Battery: " << charge_ << " ******" << std::endl;
}

NAMESPACE_END(csci3081);
