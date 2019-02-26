/**
 * @file superbot.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/superbot.h"
#include "src/superbot_motion_behavior.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Static Variables
 ******************************************************************************/
uint SuperBot::next_id_ = 0;

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
SuperBot::SuperBot(const struct superbot_params* const params) :
  Robot(params),
  frozen_(0),
  id_(-1),
  heading_angle_(0),
  angle_delta_(params->angle_delta),
  starting_pos_(params->starting_pos),
  old_pos_(params->starting_pos),
  motion_handler_(),
  motion_behavior_(),
  sensor_touch_(),
  sensor_proximity_1_(),
  sensor_proximity_2_(),
  sensor_distress_(),
  sensor_entity_type_() {
    motion_handler_.set_speed(0);
  }

SuperBot::~SuperBot(void) {
  delete this;
}


/*******************************************************************************
 * Member Functions
 ******************************************************************************/
void SuperBot::TimestepUpdate(uint dt) {
  // Update heading and speed as indicated by touch sensor
  motion_handler_.UpdateVelocity(sensor_touch_);

  motion_handler_.UpdateVelocity(sensor_proximity_1_);

  // Use velocity and position to update position
  motion_behavior_.UpdatePosition(this, dt);

  old_pos_ = get_pos();
} /* TimestepUpdate() */

void SuperBot::Accept(const EventCollision * const e) {
  sensor_touch_.Accept(e);
}

void SuperBot::Accept(const EventProximity * const e) {
  sensor_proximity_1_.Accept(e);
}

void SuperBot::Accept(const EventDistress * const e) {
  sensor_distress_.Accept(e);
}

void SuperBot::Accept(const EventEntityType * const e) {
  sensor_entity_type_.Accept(e);
}

void SuperBot::Reset(void) {
  motion_handler_.Reset();
  sensor_touch_.Reset();
  Position pos = starting_pos_;
  frozen_ = 0;
  set_pos(pos);
} /* Reset() */

NAMESPACE_END(csci3081);
