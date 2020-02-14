/**
 * @file event_keypress.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/event_keypress.h"
#include "src/graphics_arena_viewer.h"
#include "src/robot.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Turns the numerical value of the keypress into a valid type of
 * keypress used by the program.
 * @param key Numerical value of the keypress
 * @return enum event_commands Type of keypress
 */
enum event_commands EventKeypress::keypress_to_cmd(int key) {
	/*
	 * @todo These values are likely not universal across all OS's.
	 * Write a wrapper for the various OS or see if nanogui has that
	 * functionality.
	 */
	switch (key) {
	case 263:  // left arrow
		return COM_TURN_LEFT;
		break;
	case 262:  // right arrow
		return COM_TURN_RIGHT;
		break;
	case 265:  // up arrow
		return COM_SPEED_UP;
		break;
	case 264:  // down arrow
		return COM_SLOW_DOWN;
		break;
	default:  // all other keys
		printf("Unknown keypress: %d\n", key);
		assert(0);
	}
}

NAMESPACE_END(csci3081);
