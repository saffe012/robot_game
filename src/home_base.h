/**
 * @file home_base.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_HOME_BASE_H_
#define SRC_HOME_BASE_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/home_base_params.h"
#include "src/arena_immobile_entity.h"
#include "src/player.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
 /**
  * @brief Class representing the HomeBase within the Arena.
  */
class HomeBase : public Player {
 public:
  explicit HomeBase(const struct home_base_params* const params) :
    Player(params) {}


  std::string get_name(void) const override { return "Home Base"; }

  /**
   * @brief Reset the homebase to a newly constructed state (overwrites Reset()
   * in Robot class).
   */
  void Reset(void) {
    Player::Reset();
    Position pos = Position(400, 400);
    set_heading_angle(95);
    set_pos(pos);
  }

  /**
   * @brief  Pass along a collision event (from arena) to the touch sensor
   * (overwrites Accept() in Robot class).
   *
   * This method provides a framework in which sensors can get different types
   * of information from different sources. The homebase's heading will be updated
   * to move it away from the incident angle at the point of contact. Speed will
   * be updated so that it remains at 5.
   *
   * @param e The collision event.
   */
  void Accept(const EventCollision * const e) {
    Player::Accept(e);
    set_speed(5);
  }
};

NAMESPACE_END(csci3081);

#endif  // SRC_HOME_BASE_H_
