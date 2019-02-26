/**
 * @file entity_type.h
 *
 * @copyright 2017 Matt Saffert, All rights reserved.
 *
 */

#ifndef SRC_ENTITY_TYPE_H_
#define SRC_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Type Definitions
 ******************************************************************************/
/**
 * @brief Represents the types of entities in the arena
 */
enum entity_type {
  kRobot,
  kSuperBot,
  kPlayer,
  kHomebase,
  kRechargeStation,
  kWall,
  kNone
};

NAMESPACE_END(csci3081);

#endif  // SRC_ENTITY_TYPE_H_
