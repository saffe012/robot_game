/**
 * @file sensor_entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_ENTITY_TYPE_H_
#define SRC_SENSOR_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_entity_type.h"
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
 * @brief A representation of a entity type sensor.
 *
 * Entity type sensors are "active" when pressed. The sensor will
 * become active when an entity enters the entity type of a robot.
 */
class SensorEntityType : public Sensor {
 public:
  SensorEntityType();

  /**
   * @brief Get the current activation reading from the sensor.
   */
  enum entity_type activated(void) { return type_; }

  /**
   * @brief Set the current activation reading of the sensor.
   */
  void activated(enum entity_type value) { type_ = value; }

  /**
   * @brief Compute a new reading based on the entity type event.
   *
   * Note that proximity events can report "no entity type" which
   * will inactivate the sensor.
   *
   * @param an entity type event.
   *
   */
  void Accept(const EventEntityType * const e);

  /**
   * @brief Reset the entity type sensor to its newly constructed state.
   */
  void Reset(void);

 private:
  enum entity_type type_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_ENTITY_TYPE_H_
