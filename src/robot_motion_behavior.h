/**
 * @file robot_motion_behavior.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_MOTION_BEHAVIOR_H_
#define SRC_ROBOT_MOTION_BEHAVIOR_H_

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
 * @brief  Translates velocity and position to a new position. Both of these are
 * straightforward, but the framework allows for more sophisticated models of
 * motion in which each wheel has distinct speed.
 */
class RobotMotionBehavior {
 public:
  RobotMotionBehavior(void) {}

  /**
   * @brief Update the position for a Robot, based on its current
   * position and velocity.
   *
   * @param[in] ent The entitity to update.
   */
  void UpdatePosition(class ArenaMobileEntity * const ent, unsigned int dt);
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_MOTION_BEHAVIOR_H_
