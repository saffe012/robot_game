/**
 * @file event_command.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COMMAND_H_
#define SRC_EVENT_COMMAND_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdio.h>
#include "src/event_base_class.h"
#include "src/event_commands.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief An event representing a keypress command from the user that should be
 * sent to the robot.
 */
class EventCommand : public EventBaseClass {
public:
	/**
	 * @brief EventCommand constructor
	 * @param cmd User inputed command type
	 */
	explicit EventCommand(enum event_commands cmd) : cmd_(cmd) {
	}

	/**
	 * @brief Each event, upon its firing, should emit a message to the user on
	 * stdout saying what happened, in order to aid debugging.
	 */
	void EmitMessage(void) override {
		printf("Motion cmd %d received\n", cmd_);
	}

	/**
	 * @brief Gets the key command type
	 * @return enum event_commands User inputed command type
	 */
	enum event_commands cmd(void) const {
		return cmd_;
	}

private:
	enum event_commands cmd_; // User inputed command type
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_COMMAND_H_
