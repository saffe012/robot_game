/**
 * @file event_collision.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_collision.h"
#include "src/arena_mobile_entity.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructor
 ******************************************************************************/
/**
 * @brief EventCollision constructor
 */
EventCollision::EventCollision() :
	collided_(0),
	point_of_contact_(0, 0),
	angle_of_contact_(0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Each event, upon its firing, should emit a message to the user on
 * stdout saying what happened, in order to aid debugging.
 */
void EventCollision::EmitMessage(void) {
	printf("Collision event at point %f %f. Angle %f",
	       point_of_contact_.x(), point_of_contact_.y(),
	       angle_of_contact_);
}

NAMESPACE_END(csci3081);
