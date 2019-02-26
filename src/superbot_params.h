/**
 * @file superbot_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SUPERBOT_PARAMS_H_
#define SRC_SUPERBOT_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity_params.h"
#include "src/robot_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief Inherits from robot_params to set various
  * properties of the superbot.
  **/
struct superbot_params : public robot_params {
  superbot_params(void) :
      robot_params(),
      angle_delta(),
      starting_pos() {}

  uint angle_delta;
  Position starting_pos;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SUPERBOT_PARAMS_H_
