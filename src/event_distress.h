/**
 * @file event_distress.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_EVENT_DISTRESS_H_
#define SRC_EVENT_DISTRESS_H_

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
 * @brief A distress event class, which is created after a
 * \ref Robot gets within a specified distance of another entity in
 * the arena when that entity is emitting a distress call.
 */
class EventDistress : public EventBaseClass {
public:
	/**
	 * @brief EventDistress constructor
	 */
	EventDistress(void);

	/**
	 * @brief Each event, upon its firing, should emit a message to the user on
	 * stdout saying what happened, in order to aid debugging.
	 */
	void EmitMessage(void) override;

	/**
	 * @brief Gets collided_. If \c TRUE, then this instance represents an active distress with
	 * a distress signal. If \c FALSE, then it represents a previous distress
	 * event that has been resolved.
	 * @return int 1 represents collison happened, 0 no collision
	 */
	int collided(void) const {
		return collided_;
	}

	/**
	 * @brief Sets collided_. If \c TRUE, then this instance represents an active distress with
	 * a distress signal. If \c FALSE, then it represents a previous distress
	 * event that has been resolved.
	 * @param c 1 represents collison happened, 0 no collision
	 */
	void collided(int c) {
		collided_ = c;
	}

	/**
	 * @brief Gets the point in the arena at which the entity has collided with
	 * distress signal
	 * @return Position Position of the point of contact
	 */
	Position point_of_contact(void) const {
		return point_of_contact_;
	}

	/**
	 * @brief Sets the point in the arena at which the entity has collided with
	 * distress signal
	 * @param p Position of the point of contact
	 */
	void point_of_contact(Position p) {
		point_of_contact_ = p;
	}


private:
	int collided_; // 0 if value no collision, 1 represents collision occured
	Position point_of_contact_; // Position of the point of contact
};

NAMESPACE_END(csci3081);

#endif  // SRC_EVENT_DISTRESS_H_
