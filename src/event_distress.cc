/**
 * @file event_distress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_distress.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventDistress::EventDistress() :
  collided_(0),
  point_of_contact_(0, 0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventDistress::EmitMessage(void) {
  printf("Distress event at point %f %f.",
         point_of_contact_.x(), point_of_contact_.y());
} /* EmitMessage() */

NAMESPACE_END(csci3081);
