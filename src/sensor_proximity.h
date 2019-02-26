/**
 * @file sensor_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_SENSOR_PROXIMITY_H_
#define SRC_SENSOR_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <vector>
#include <utility>

#include "src/common.h"
#include "src/event_proximity.h"
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
 * @brief A representation of a proximity sensor.
 *
 * Proximity sensors are "active" when pressed. For our purposes, imagine
 * a single cone emanating form the center of the robot split into two cones.
 * These two cones represent the field of voew of the sensors. The sensor will
 * become active when an entity enters the field of view.
 */

class SensorProximity : public Sensor {
 public:
  SensorProximity();

  /**
   * @brief Get the current activation reading from the sensor.
   */
  int activated(void) { return activated_; }

  /**
   * @brief Set the current activation reading of the sensor.
   */
  void activated(int value) { activated_ = value; }

  // Getters and setters

  /**
   * @brief Gets the position of where a sensor touches an entity
   */
  Position point_of_contact() { return point_of_contact_; }

  /**
   * @brief Sets the position of where a sensor touches an entity
   */
  void point_of_contact(Position p) {
    point_of_contact_ = p;
  }

  /**
   * @brief Gets the field of view of the sensor
   */
  double field_of_view(void) { return field_of_view_; }

  /**
   * @brief Sets the field of view of the sensor
   */
  void field_of_view(double fov) { field_of_view_ = fov; }

  /**
   * @brief Gets the angle of contact of two entities
   */
  double angle_of_contact(void) { return angle_of_contact_; }

  /**
   * @brief Sets the angle of contact of two entities
   */
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

  /**
   * @brief Gets the range of the sensor
   */
  double range(void) { return range_; }

  /**
   * @brief Sets the range of the sensor
   */
  void range(double value) { range_ = value; }

  /**
   * @brief Compute a new reading based on the proximity event.
   *
   * Note that proximity events can report "no proximity" which
   * will inactivate the sensor.
   *
   * @param a proximity event
   *
   */
  void Accept(const EventProximity * const e);

  /**
   * @brief Reset the proximity sensor to its newly constructed state.
   */
  void Reset(void);

 private:
  int activated_;
  Position point_of_contact_;
  double angle_of_contact_;
  double range_;
  double field_of_view_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_SENSOR_PROXIMITY_H_
