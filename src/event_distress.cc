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
/**
 * @brief EventDistress constructor
 */
EventDistress::EventDistress() :
	collided_(0),
	point_of_contact_(0, 0) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Each event, upon its firing, should emit a message to the user on
 * stdout saying what happened, in order to aid debugging.
 */
void EventDistress::EmitMessage(void) {
	printf("Distress event at point %f %f.",
	       point_of_contact_.x(), point_of_contact_.y());
}

NAMESPACE_END(csci3081);
