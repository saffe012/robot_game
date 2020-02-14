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
/**
 * @brief SensorDistress constructor
 */
SensorDistress::SensorDistress(void) :
	activated_(false) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Compute a new reading based on the distress event.
 * Note that distress events can report "no distress" which
 * will inactivate the sensor.
 * @param e A distress event.
 */
void SensorDistress::Accept(const EventDistress * const e) {
	if (e->collided()) {
		activated_ = 1;
	} else {
		activated_ = 0;
	}
}

/**
 * @brief Reset the distress sensor to its newly constructed state.
 */
void SensorDistress::Reset(void) {
	activated_ = false;
}

NAMESPACE_END(csci3081);
