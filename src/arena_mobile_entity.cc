/**
 * @file arena_mobile_entity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/arena_mobile_entity.h"
#include "src/robot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Update an entity's position and velocity after the specified # of
 * timesteps has elapsed.
 *
 * @param dt The # of timesteps that has elapsed since the last time
 *   position/velocity were updated.
 */
void ArenaMobileEntity::TimestepUpdate(uint dt) {
	RobotMotionBehavior h;
	h.UpdatePosition(this, dt);
}

NAMESPACE_END(csci3081);
