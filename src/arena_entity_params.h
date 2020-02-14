/**
 * @file arena_entity_params.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_ENTITY_PARAMS_H_
#define SRC_ARENA_ENTITY_PARAMS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <nanogui/nanogui.h>
#include "src/common.h"
#include "src/position.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Structure Definitions
 ******************************************************************************/
/**
 * @brief Defines the parameters for the arena entities.
 */
struct arena_entity_params {
	arena_entity_params(void) : radius(), pos(), color() {
	}

	double radius; // radius of entity in pixels
	Position pos; // holds x and y coordinates of the entity in the arena
	csci3081::Color color; // holds color of entity in arena in RGBA
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_ENTITY_PARAMS_H_
