/**
 * @file sensor_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_distress.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorDistress::SensorDistress(void) :
  activated_(false) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void SensorDistress::Accept(const EventDistress * const e) {
  if (e->collided()) {
    activated_ = 1;
  } else {
    activated_ = 0;
  }
}

void SensorDistress::Reset(void) {
  activated_ = false;
} /* reset() */

NAMESPACE_END(csci3081);
