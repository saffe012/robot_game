/**
 * @file sensor_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <limits>
#include "src/sensor_proximity.h"
#include "src/arena_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SensorProximity::SensorProximity(void) :
	activated_(false),
	point_of_contact_(0, 0),
	angle_of_contact_(0),
	range_(50),
	field_of_view_(30) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Compute a new reading based on the proximity event.
 * Note that proximity events can report "no proximity" which
 * will inactivate the sensor.
 * @param a proximity event
 */
void SensorProximity::Accept(const EventProximity * const e) {
	if (e->activated()) {
		activated_ = 1;
		point_of_contact_ = e->point_of_contact();
		angle_of_contact_ = e->angle_of_contact();
	}
	else {
		activated_ = 0;
	}
}

/**
 * @brief Reset the proximity sensor to its newly constructed state.
 */
void SensorProximity::Reset(void) {
	activated_ = false;
}

NAMESPACE_END(csci3081);
