/**
 * @file home_base_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_PARAMS_H_
#define SRC_HOME_BASE_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity_params.h"
#include "src/player_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
  * @brief Define the parameter for the HomeBase.
  */
struct home_base_params : public player_params {
  home_base_params(void) :
      player_params() {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_HOME_BASE_PARAMS_H_
