/**
 * @file event_recharge.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_RECHARGE_H_
#define SRC_EVENT_RECHARGE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An event representing an encounter (really a collision) that a robot
 * has with a \ref RechargeStation.
 */
class EventRecharge : public EventBaseClass {
public:
	/**
	 * @brief EventRecharge constructor
	 */
	EventRecharge(void) {
	}

	/**
	 * @brief Each event, upon its firing, should emit a message to the user on
	 * stdout saying what happened, in order to aid debugging.
	 */
	void EmitMessage(void) override {
		printf("Robot Battery recharged!\n");
	}
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_RECHARGE_H_
