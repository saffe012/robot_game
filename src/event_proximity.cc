/**
 * @file event_proximity.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_proximity.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
EventProximity::EventProximity() :
  collided_(0),
  point_of_contact_(0, 0),
  angle_of_contact_(0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void EventProximity::EmitMessage(void) {
  printf("Proximity event at point %f %f. Angle %f",
         point_of_contact_.x(), point_of_contact_.y(),
         angle_of_contact_);
} /* EmitMessage() */

NAMESPACE_END(csci3081);
