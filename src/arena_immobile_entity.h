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
  ArenaImmobileEntity(double radius, const Position& pos,
                    const csci3081::Color& color) :
      ArenaEntity(radius, pos, color) {}
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_IMMOBILE_ENTITY_H_
