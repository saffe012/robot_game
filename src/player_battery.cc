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
double PlayerBattery::Deplete(__unused Position old_pos,
  __unused Position new_pos, __unused double dt) {
  double ys, xs;

  xs = pow(old_pos.x() - new_pos.x(), 2);
  ys = pow(old_pos.y() - new_pos.y(), 2);

  int distance;

  distance = pow((xs + ys), .5);

  charge_ = charge_ - (distance * .01);

  if (charge_ < 0)
    charge_ = 0;

  return charge_;
} /* deplete() */

void PlayerBattery::Accept(__unused const EventCollision * const e) {
  if (e->collided()) {
    charge_ -= 5;
  }
  if (charge_ < 0)
    charge_ = 0;

  // std::cout << "******Battery: " << charge_ << " ******" << std::endl;
}

NAMESPACE_END(csci3081);
