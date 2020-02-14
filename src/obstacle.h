/**
 * @file obstacle.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_OBSTACLE_H_
#define SRC_OBSTACLE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/arena_immobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing an obstacle within the arena.
 */
class Obstacle : public ArenaImmobileEntity {
public:
	/**
	 * Obstacle constructor
	 * @param radius Radius of entity in pixels
	 * @param pos Holds x and y coordinates of the entity in the arena
	 * @param color Holds color of entity in arena in RGBA
	 */
	Obstacle(double radius, const Position& pos,
	         const csci3081::Color& color);

	/**
	 * @brief Gets the name of class
	 * @return String The string "Obstacle" + id
	 */
	std::string get_name(void) const override {
		return "Obstacle" + std::to_string(id_);
	}

private:
	static uint next_id_; // id of next obstacle
	int id_; // id of obstacle
};

NAMESPACE_END(csci3081);

#endif  // SRC_OBSTACLE_H_
