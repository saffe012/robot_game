/**
 * @file arena_immobile_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_IMMOBILE_ENTITY_H_
#define SRC_ARENA_IMMOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An immobile entity in the arena.
 *
 * Immobile entities cannot move, and therefore do not need to override the
 * \ref TimestepUpdate() function.
 */
class ArenaImmobileEntity : public ArenaEntity {
public:
	/**
	 * @brief ArenaImmobileEntity constructor
	 * @param radius Radius of entity in pixels
	 * @param pos Holds x and y coordinates of the entity in the arena
	 * @param color Holds color of entity in arena in RGBA
	 */
	ArenaImmobileEntity(double radius, const Position& pos,
	                    const csci3081::Color& color) : ArenaEntity(radius, pos, color) {
	}
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_IMMOBILE_ENTITY_H_
