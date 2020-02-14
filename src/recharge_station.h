/**
 * @file recharge_station.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

#ifndef SRC_RECHARGE_STATION_H_
#define SRC_RECHARGE_STATION_H_

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include <string>
#include "src/obstacle.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Class Definitions
 ******************************************************************************/
/**
 * @brief A class representing a recharge station within the arena that is used
 * to recharge player batteries.
 */
class RechargeStation : public Obstacle {
public:
	/**
	 * @brief RechargeStation constructor
	 * @param radius RechargeStation's radius
	 * @param pos RechargeStation's position
	 * @param color RechargeStation's color
	 */
	RechargeStation(double radius, const Position& pos,
	                const csci3081::Color& color) :
		Obstacle(radius, pos, color) {
	}

	/**
	 * @brief Gets the name of the RechargeStation
	 * @return std::string The name of the RechargeStation: "Recharge Station"
	 */
	std::string get_name(void) const override {
		return "Recharge Station";
	}
};

NAMESPACE_END(csci3081);

#endif  // SRC_RECHARGE_STATION_H_
