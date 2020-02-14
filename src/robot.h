/**
 * @file robot.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_ROBOT_H_
#define SRC_ROBOT_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/robot_motion_handler.h"
#include "src/robot_motion_behavior.h"
#include "src/sensor_touch.h"
#include "src/arena_mobile_entity.h"
#include "src/event_entity_type.h"
#include "src/event_collision.h"
#include "src/event_proximity.h"
#include "src/event_distress.h"
#include "src/sensor_entity_type.h"
#include "src/sensor_proximity.h"
#include "src/sensor_distress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief Class representing a mobile robot within the arena.
 *
 * Robots have the capability of updating their own position when asked, and
 * also track their own velocity and heading. They have a touch sensor for
 * responding to collision events which is activated/deactivated on collision
 * events.
 *
 */
class Robot : public ArenaMobileEntity {
public:
	/**
	 * @brief Robot constructor
	 * @param params Parameters of the robot
	 */
	explicit Robot(const struct robot_params* const params);

	/**
	 * @brief Robot destructor
	 */
	~Robot(void);

	/**
	 * @brief Reset the robot to a newly constructed state (needed for reset
	 * button to work in arena GUI).
	 */
	void Reset(void) override;

	/**
	 * @brief Update the robot's position and velocity after the specified
	 * duration has passed.
	 * @param dt The # of timesteps that have elapsed since the last update.
	 */
	void TimestepUpdate(unsigned int dt) override;

	/**
	 * @brief  Pass along a collision event (from arena) to the touch sensor.
	 * This method provides a framework in which sensors can get different types
	 * of information from different sources. The robot's heading will be updated
	 * to move it away from the incident angle at the point of contact.
	 * @param e The collision event.
	 */
	void Accept(const EventCollision * const e) override;

	/**
	 * @brief  Pass along a proximity event (from arena) to the proximity sensor.
	 * This method provides a framework in which sensors can get different types
	 * of information from different sources. The robot's heading will be updated
	 * to move it away from the incident angle at the point of contact.
	 * @param e The proximity event.
	 */
	void Accept(const EventProximity * const e);

	/**
	 * @brief  Pass along a distress event (from arena) to the distress sensor.
	 * This method provides a framework in which sensors can get different types
	 * of information from different sources. The robot's heading will be updated
	 * to move it away from the incident angle at the point of contact.
	 * @param e The distress event.
	 */
	void Accept(const EventDistress * const e);


	/**
	 * @brief  Pass along an entity type event (from arena) to the entity type sensor.
	 * This method provides a framework in which sensors can get different types
	 * of information from different sources. The robot's heading will be updated
	 * to move it away from the incident angle at the point of contact.
	 * @param e The entity type event.
	 */
	void Accept(const EventEntityType * const e);

	/**
	 * @brief Gets the range of the proximity sensor
	 * @return double The range of the proximity sensor
	 */
	double get_proximity_range(void) {
		return sensor_proximity_1_.range();
	}

	/**
	 * @brief Gets the heading angle of the robot
	 * @return double Angle in degrees the robot is travelling
	 */
	double get_heading_angle(void) const override {
		return motion_handler_.get_heading_angle();
	}

	/**
	 * @brief Sets the heading angle of the robot
	 * @param ha Angle in degrees the robot is travelling
	 */
	void set_heading_angle(double ha) override {
		motion_handler_.set_heading_angle(ha);
	}

	/**
	 * @brief Gets the speed of the robot
	 * @return double Speed of the robot
	 */
	double get_speed(void) const override {
		return motion_handler_.get_speed();
	}

	/**
	 * @brief Sets the speed of the robot
	 * @param sp Speed of the robot
	 */
	void set_speed(double sp) override {
		motion_handler_.set_speed(sp);
	}

	/**
	 * @brief Sets whether a robot is frozen or not
	 * @param froze Boolean to show whether a robot is frozen or not
	 */
	void set_frozen(int froze) {
		frozen_ = froze;
	}

	/**
	 * @brief Gets whether a robot is frozen or not
	 * @return int Boolean to show whether a robot is frozen or not
	 */
	int get_frozen(void) {
		return frozen_;
	}

	/**
	 * @brief Sets if robot has been collided with by home base
	 * @param super Boolean to show if robot has been collided with by home base
	 */
	void set_super(int super) {
		super_ = super;
	}

	/**
	 * @brief Gets if robot has been collided with by home base
	 * @return int Boolean to show if robot has been collided with by home base
	 */
	int get_super(void) {
		return super_;
	}

	/**
	 * @brief Gets the name of the robot
	 * @return std::string The name of the Robot: "Robot"
	 */
	std::string get_name(void) const override {
		return "Robot";
	}

private:
	static unsigned int next_id_; // id of the next robot in system
	int frozen_; // boolean to show whether robot is frozen or not
	int super_; // boolean to show if robot has been collided with by home base
	int id_; // id of this robot
	double heading_angle_; // angle in degrees the robot is travelling
	double angle_delta_; // change in heading anlge of robot since last update
	Position starting_pos_; // starting position of robot
	Position old_pos_; // position of robot at last simulation update
	MotionHandlerRobot motion_handler_; // controls robots actuators
	RobotMotionBehavior motion_behavior_; // handles changes in player velocity or direction
	SensorTouch sensor_touch_; // touch sensor associated with robot
	SensorProximity sensor_proximity_1_; // proximity sensor 1 associated with robot
	SensorProximity sensor_proximity_2_; // proximity sensor 2 associated with robot
	SensorDistress sensor_distress_; // distress sensor associated with robot
	SensorEntityType sensor_entity_type_; // sensor to detect the entity of near by entities
};

NAMESPACE_END(csci3081);

#endif  // SRC_ROBOT_H_
