/**
 * @file event_keypress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_KEYPRESS_H_
#define SRC_EVENT_KEYPRESS_H_

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
 * @brief An event representing that a key on the keyboard has been
 * pressed.
 *
 * They are sent from the graphics framework to the \ref GraphicsArenaViewer,
 * where they are interpreted further
 */
class EventKeypress : public EventBaseClass {
public:
	/**
	 * @brief EventKeypress constructor
	 * @param key Numerical value of the keypress
	 */
	explicit EventKeypress(int key) : key_(key) {
	}

	/**
	 * @brief Each event, upon its firing, should emit a message to the user on
	 * stdout saying what happened, in order to aid debugging.
	 */
	void EmitMessage(void) override {
		printf("Keypress command received\n");
	}

	/**
	 * @brief Turns the numerical value of the keypress into a valid type of
	 * keypress used by the program.
	 * @param key Numerical value of the keypress
	 * @return enum event_commands Type of keypress
	 */
	enum event_commands keypress_to_cmd(int key);

private:
	int key_; // Numerical value of the keypress
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_KEYPRESS_H_
