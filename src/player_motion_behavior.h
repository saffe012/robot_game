/**
 * @file player_motion_behavior.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_PLAYER_MOTION_BEHAVIOR_H_
#define SRC_PLAYER_MOTION_BEHAVIOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <Eigen/Dense>
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Manages the modification to the velocity based on user
 * input and collisions.
 *
 * Translates velocity and position to a new position. Both of these are
 * straightforward, but the framework allows for more sophisticated models of
 * motion in which each wheel has distinct speed.
 */
class PlayerMotionBehavior {
public:
	/**
	 * @brief PlayerMotionBehavior constructor
	 */
	PlayerMotionBehavior(void) {
	}

	/**
	 * @brief Update the position for an ArenaEntity, based on its current
	 * position and velocity.
	 * @param ent The entitity to update.
	 * @param dt The change in time of the simulation
	 */
	void UpdatePosition(class ArenaMobileEntity * const ent, unsigned int dt);
};

NAMESPACE_END(csci3081);

#endif  // SRC_PLAYER_MOTION_BEHAVIOR_H_
