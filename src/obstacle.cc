/**
 * @file obstacle.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint Obstacle::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
/**
 * Obstacle constructor
 * @param radius Radius of entity in pixels
 * @param pos Holds x and y coordinates of the entity in the arena
 * @param color Holds color of entity in arena in RGBA
 */
Obstacle::Obstacle(double radius, const Position& pos,
                   const csci3081::Color& color) :
	ArenaImmobileEntity(radius, pos, color), id_(-1) {
	id_ = next_id_++;
}

NAMESPACE_END(csci3081);
