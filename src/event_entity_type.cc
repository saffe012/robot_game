/**
 * @file event_entity_type.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_entity_type.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventEntityType::EventEntityType() :
  type_(kNone),
  point_of_contact_(Position(0, 0)) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventEntityType::EmitMessage(void) {
  printf("EntityType event at point %f %f.",
         point_of_contact_.x(), point_of_contact_.y());
} /* EmitMessage() */

NAMESPACE_END(csci3081);
