/**
 * @file event_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESS_H_
#define SRC_EVENT_DISTRESS_H_

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
 * @brief A distress event class, which is created after a
 * \ref Robot gets within a specified distance of another entity in
 * the arena when that entity is emitting a distress call.
 */
class EventDistress : public EventBaseClass {
 public:
  EventDistress(void);
  void EmitMessage(void) override;

  /**
   * @brief If \c TRUE, then this instance represents an active distress with
   * a distress signal. If \c FALSE, then it represents a previous distress
   * event that has been resolved.
   */
  int collided(void) const { return collided_; }
  void collided(int c) { collided_ = c; }

  /**
   * @brief The point in the arena at which the entity has collided with
   * distress signal
   */
  Position point_of_contact(void) const { return point_of_contact_; }
  void point_of_contact(Position p) { point_of_contact_ = p; }


 private:
  int collided_;
  Position point_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_DISTRESS_H_
