/**
 * @file event_collision.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_COLLISION_H_
#define SRC_EVENT_COLLISION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <stdlib.h>
#include "src/event_base_class.h"
#include "src/position.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A collision event class, which is created after a
 * \ref MobileArenaEntity gets within a specified distance of another entity in
 * the arena, OR when an entity that was previously within the collision delta
 * of other entity outside of that threshold.
 */
class EventCollision : public EventBaseClass {
public:
	/**
	 * @brief EventCollision constructor
	 */
	EventCollision(void);

	/**
	 * @brief Each event, upon its firing, should emit a message to the user on
	 * stdout saying what happened, in order to aid debugging.
	 */
	void EmitMessage(void) override;

	/**
	 * @brief If TRUE, then this instance represents an active collision
	 * event. If FALSE, then it represents a previous collision event that has
	 * been resolved.
	 * @return int 1 represents collison happened, 0 no collision
	 */
	int collided(void) const {
		return collided_;
	}

	/**
	 * @brief Sets the value of collided
	 * @param c 0 if value no collision, 1 represents collision
	 */
	void collided(int c) {
		collided_ = c;
	}

	/**
	 * @brief Gets the point in the arena at which the entities have collided/touched.
	 * @return Position Position of the point of contact
	 */
	Position point_of_contact(void) const {
		return point_of_contact_;
	}

	/**
	 * @brief Sets the point in the arena at which the entities have collided/touched.
	 * @param p Position of the point of contact
	 */
	void point_of_contact(Position p) {
		point_of_contact_ = p;
	}

	/**
	 * @brief Gets the angle, in degrees, as specified on the unit circle, that the
	 * collision occurred at. Needed to calculate the outgoing/bounceback angle.
	 * @return double Angle in degrees of the line of contact
	 */
	double angle_of_contact(void) const {
		return angle_of_contact_;
	}

	/**
	 * @brief Sets the angle, in degrees, as specified on the unit circle, that the
	 * collision occurred at. Needed to calculate the outgoing/bounceback angle.
	 * @return double Angle in degrees of the line of contact
	 */
	void angle_of_contact(double aoc) {
		angle_of_contact_ = aoc;
	}

private:
	int collided_; // 0 if value no collision, 1 represents collision occured
	Position point_of_contact_; // Position of the point of contact
	double angle_of_contact_; // Angle in degrees of the line of contact
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_COLLISION_H_
