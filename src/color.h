/**
 * @file color.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_COLOR_H_
#define SRC_COLOR_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/common.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A simple representation of a position of an entity within the arena.
 */
struct Color {
public:
	Color(void) : r(0), g(0), b(0), a(255) { // default : black
	}
	Color(int in_r, int in_g, int in_b, int in_a)
		: r(in_r), g(in_g), b(in_b), a(in_a) {
	}

	int r; // red
	int g; // green
	int b; // blue
	int a; // alpha
};

NAMESPACE_END(csci3081);

#endif  // SRC_COLOR_H_
