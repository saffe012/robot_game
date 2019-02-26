/**
 * @file event_proximity.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_PROXIMITY_H_
#define SRC_EVENT_PROXIMITY_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A proximity event class, which is created after a
 * \ref Robot gets within a specified distance of another entity in
 * the arena, OR when an entity that was previously within the collision delta
 * of other entity outside of that threshold.
 */
class EventProximity : public EventBaseClass {
 public:
  EventProximity(void);
  void EmitMessage(void) override;

  /**
   * @brief If \c TRUE, then this instance represents an active proximity
   * event. If \c FALSE, then it represents a previous proximity event that has
   * been resolved.
   */
  int activated(void) const { return collided_; }
  void activated(int c) { collided_ = c; }

  /**
   * @brief The point in the arena at which the entities have been in proximity.
   */
  Position point_of_contact(void) const { return point_of_contact_; }
  void point_of_contact(Position p) { point_of_contact_ = p; }

  /**
   * @brief The angle, in degrees, as specified on the unit circle, that the
   * proximity occurred at. Needed to calculate the outgoing/bounceback angle.
   */
  double angle_of_contact(void) const { return angle_of_contact_; }
  void angle_of_contact(double aoc) { angle_of_contact_ = aoc; }

 private:
  int collided_;
  Position point_of_contact_;
  double angle_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_PROXIMITY_H_
