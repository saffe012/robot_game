/**
 * @file superbot_motion_handler.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/superbot_motion_handler.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
MotionHandlerSuperBot::MotionHandlerSuperBot() :
    heading_angle_(0),
  speed_(0),
  max_speed_(15) {
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

void MotionHandlerSuperBot::UpdateVelocity(SensorTouch st) {
  // std::cout << "Heading angle: " << heading_angle_ << std::endl;
  if (st.activated()) {
    heading_angle_ = - st.angle_of_contact();
    if (heading_angle_ < 0) {
      heading_angle_ += 360;
    }
  }
}

void MotionHandlerSuperBot::UpdateVelocity(SensorProximity sp) {
  // std::cout << "Heading angle: " << heading_angle_ << std::endl;
  if (sp.activated()) {
    heading_angle_ = sp.angle_of_contact() + 15;
    if (heading_angle_ < 0) {
      heading_angle_ += 360;
    }
  }
}

void MotionHandlerSuperBot::Reset() {
  heading_angle_ = get_heading_angle();
  speed_ = 5;
}

NAMESPACE_END(csci3081);
