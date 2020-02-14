/**
 * @file position.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_POSITION_H_
#define SRC_POSITION_H_

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
struct Position {
public:
	/**
	 * @brief Position constructor
	 */
	Position(void) : x_(0), y_(0) {
	}
	/**
	 * @brief Position constructor
	 * @param in_x Position's x coordinate
	 * @param in_y Position's y coordinate
	 */
	Position(int in_x, int in_y) : x_(in_x), y_(in_y) {
	}

	/**
	 * @brief Get position's x coordinate
	 * @return double Position's x coordinate
	 */
	double x(void) const {
		return x_;
	}

	/**
	 * @brief Get position's y coordinate
	 * @return double Position's y coordinate
	 */
	double y(void) const {
		return y_;
	}

	/**
	 * @brief Set position's x coordinate
	 * @param x Position's x coordinate
	 */
	void x(double x) {
		x_ = x;
	}

	/**
	 * @brief Set position's y coordinate
	 * @param y Position's y coordinate
	 */
	void y(double y) {
		y_ = y;
	}

	/**
	 * @brief Equals sign override for Positions
	 */
	Position& operator=(const Position& other) {
		this->x_ = other.x_;
		this->y_ = other.y_;
		return *this;
	}

private:
	int x_; // Position's x coordinate
	int y_; // Position's y coordinate
};

NAMESPACE_END(csci3081);

#endif  // SRC_POSITION_H_
