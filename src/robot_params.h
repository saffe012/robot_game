/**
 * @file robot_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_PARAMS_H_
#define SRC_ROBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief Inherits from mobile_entity_params to set various
  * properties of the robot.
  **/
struct robot_params : public arena_mobile_entity_params {
  robot_params(void) :
      arena_mobile_entity_params(),
      angle_delta(),
      starting_pos() {}

  uint angle_delta;
  Position starting_pos;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_PARAMS_H_
