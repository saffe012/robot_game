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
	// player() : player_params(arena_mobile_entity_params(arena_entity_params(radius(), pos(), color()), collision_delta()), battery_max_charge(), angle_delta())
	// recharge_station() : arena_entity_params(radius(), pos(), color())
	// home_base() : home_base_params(player_params(arena_mobile_entity_params(arena_entity_params(radius(), pos(), color()), collision_delta()), battery_max_charge(), angle_delta()))
	// obstacles() : arena_entity_params(radius(), pos(), color())
	// robots() : robot_params(arena_mobile_entity_params(arena_mobile_entity_params(arena_entity_params(radius(), pos(), color()), collision_delta())), angle_delta(), starting_pos())
	// superbots() : superbot_params(robot_params(arena_mobile_entity_params(arena_mobile_entity_params(arena_entity_params(radius(), pos(), color()), collision_delta())), angle_delta(), starting_pos()), angle_delta(), starting_pos())
	arena_params(void) : player(), recharge_station(), home_base(), obstacles(),
		robots(), superbots(), n_superbots(), n_obstacles(), n_robots(), x_dim(), y_dim() {
	}

	struct player_params player; // parameters for the player entity
	struct arena_entity_params recharge_station; // parameters for the recharge station arena entity
	struct home_base_params home_base; // parameters for the home base arena entity
	struct arena_entity_params obstacles[MAX_OBSTACLES]; // parameters for the obstacle arena entities
	struct robot_params robots[MAX_ROBOTS]; // parameters for the robots
	struct superbot_params superbots[MAX_ROBOTS]; // parameters for the superbots
	size_t n_superbots; // number of SuperBots in the arena
	size_t n_obstacles; // number of Obstacles in the arena
	size_t n_robots; // number of Robots in the arena
	uint x_dim; // number of pixels wide the arena is
	uint y_dim; // number of pixels tall the arena is
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_PARAMS_H_
