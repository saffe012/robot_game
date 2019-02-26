/**
 * @file arena_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 *
 */

#ifndef SRC_ARENA_PARAMS_H_
#define SRC_ARENA_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/robot_params.h"
#include "src/player_params.h"
#include "src/home_base_params.h"
#include "src/superbot_params.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constant Definitions
 ******************************************************************************/
#define MAX_OBSTACLES 8
#define MAX_ROBOTS 8
/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
 /**
 * @brief Define the parameter for the arena.
 *
 * This includes the arena geometry as well as the parameters for \c ALL
 * entities within the arena.
 */
struct arena_params {
  arena_params(void) : player(), recharge_station(), home_base(), obstacles(),
                        robots(), superbots(), n_superbots(), n_obstacles(),
                        n_robots(), x_dim(), y_dim() {}

  struct player_params player;
  struct arena_entity_params recharge_station;
  struct home_base_params home_base;
  struct arena_entity_params obstacles[MAX_OBSTACLES];
  struct robot_params robots[MAX_ROBOTS];
  struct superbot_params superbots[MAX_ROBOTS];
  size_t n_superbots;
  size_t n_obstacles;
  size_t n_robots;
  uint x_dim;
  uint y_dim;
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_PARAMS_H_
