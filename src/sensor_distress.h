/**
 * @file sensor_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_DISTRESS_H_
#define SRC_SENSOR_DISTRESS_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_distress.h"
#include "src/sensor.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Classes
 ******************************************************************************/
class ArenaEntity;

/**
 * @brief A representation of a distress sensor.
 *
 * distress sensors are "active" when pressed. The sensor will
 * become active when an entity with a ditress signal enters the range of the
 * proximity sensor.
 */
class SensorDistress : public Sensor {
public:
	/**
	 * @brief SensorDistress constructor
	 */
	SensorDistress();

	/**
	 * @brief Get the current activation reading from the sensor.
	 * @return int Boolean to represent if sensor is active
	 */
	int activated(void) {
		return activated_;
	}

	/**
	 * @brief Set the current activation reading of the sensor.
	 * @param value Boolean to represent if sensor is active
	 */
	void activated(int value) {
		activated_ = value;
	}

	/**
	 * @brief Compute a new reading based on the distress event.
	 * Note that distress events can report "no distress" which
	 * will inactivate the sensor.
	 * @param e A distress event.
	 */
	void Accept(const EventDistress * const e);

	/**
	 * @brief Reset the distress sensor to its newly constructed state.
	 */
	void Reset(void);

private:
	int activated_; // Boolean to represent if sensor is active
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_DISTRESS_H_
