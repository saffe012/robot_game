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
/**
 * @brief SensorEntityType constructor
 */
SensorEntityType::SensorEntityType(void) : type_(kNone) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Compute a new reading based on the entity type event.
 * Note that proximity events can report "no entity type" which
 * will inactivate the sensor.
 * @param an entity type event.
 */
void SensorEntityType::Accept(const EventEntityType * const e) {
	if (e->activated() != kNone) {
		type_ = e->activated();
	}
}

/**
 * @brief Reset the entity type sensor to its newly constructed state.
 */
void SensorEntityType::Reset(void) {
	type_ = kNone;
}

NAMESPACE_END(csci3081);
