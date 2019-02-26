/**
 * @file event_entity_type.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_ENTITY_TYPE_H_
#define SRC_EVENT_ENTITY_TYPE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"
#include "src/entity_type.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An entity type event class, which is created when a robot is in the
 * proximity of another entity. It will emit the type of the entity that is close
 */
class EventEntityType : public EventBaseClass {
 public:
  EventEntityType(void);
  void EmitMessage(void) override;

  /**
   * @brief If \c TRUE, then this instance represents an active entity type
   * event. If \c FALSE, then it represents a previous entity type event that has
   * been resolved.
   */
  enum entity_type activated(void) const { return type_; }
  void activated(enum entity_type c) { type_ = c; }

  /**
   * @brief The point in the arena at which the entities have been in proximity.
   */
  Position point_of_contact(void) const { return point_of_contact_; }
  void point_of_contact(Position p) { point_of_contact_ = p; }

 private:
  enum entity_type type_;
  Position point_of_contact_;
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_ENTITY_TYPE_H_
