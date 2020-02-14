/**
 * @file mobile_arena_entity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ARENA_MOBILE_ENTITY_H_
#define SRC_ARENA_MOBILE_ENTITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <algorithm>
#include <iostream>
#include "src/arena_entity.h"
#include "src/event_base_class.h"
#include "src/event_recharge.h"
#include "src/event_collision.h"
#include "src/color.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A mobile entity in the arena, capable of updating its own position
 * and/or velocity when asked by the simulation.
 *
 * All mobile entities must have a heading angle so that their orientation can
 * be properly drawn by the viewer.
 */
class ArenaMobileEntity : public ArenaEntity {
public:
	/**
	 * @brief ArenaMobileEntity constructor
	 * @param radius Radius of entity in pixels
	 * @param collision_delta Minimum distance between entities that qualifies as a collision.
	 * @param pos Holds x and y coordinates of the entity in the arena
	 * @param color Holds color of entity in arena in RGBA
	 */
	ArenaMobileEntity(double radius, double collision_delta,
	                  const Position& pos, const csci3081::Color& color) :
		ArenaEntity(radius, pos, color),
		collision_delta_(collision_delta) {
	}

	/**
	 * @brief Get the current heading angle for the entity.
	 */
	virtual double get_heading_angle(void) const = 0;

	/**
	 * @brief Set the new heading angle for the entity.
	 *
	 * This should only be called by a dedicated motion handler class, and only
	 * from within \ref Timestepupdate().
	 *
	 * @param heading_angle Direction of travel of entity in degrees
	 */
	virtual void set_heading_angle(double heading_angle) = 0;

	/**
	 * @brief Get the current speed of an arena entity.
	 */
	virtual double get_speed(void) const = 0;

	/**
	 * @brief Set the new speed of an entity.
	 *
	 * This should only be called by a dedicated motion handler class, and only
	 * from within \ref Timestepupdate().
	 *
	 * @param sp Speed of entity in pixels per second
	 */
	virtual void set_speed(double sp) = 0;

	/**
	 * @brief Accept a visit from a collision event, updating state appropriately.
	 * @param e An EventCollision that holds info about an entity's collion
	 */
	virtual void Accept(const EventCollision * const e) = 0;

	/**
	 * @brief Update an entity's position and velocity after the specified # of
	 * timesteps has elapsed.
	 *
	 * @param dt The # of timesteps that has elapsed since the last time
	 *   position/velocity were updated.
	 */
	void TimestepUpdate(uint dt) override;

	/**
	 * @brief Get the minimum distance between two arena entities that will be
	 * considered a collision.
	 */
	double get_collision_delta(void) const {
		return collision_delta_;
	}

private:
	double collision_delta_; // Minimum distance between entities that qualifies as a collision.
};

NAMESPACE_END(csci3081);

#endif  // SRC_ARENA_MOBILE_ENTITY_H_
