/**
 * @file sensor_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_entity_type.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorEntityType::SensorEntityType(void) : type_(kNone) {}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorEntityType::Accept(const EventEntityType * const e) {
  if (e->activated() != kNone) {
    type_ = e->activated();
  }
}

void SensorEntityType::Reset(void) {
  type_ = kNone;
} /* reset() */

NAMESPACE_END(csci3081);
