/**
 * @file main.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include "src/arena_params.h"
#include "src/color.h"

/*******************************************************************************
 * Non-Member Functions
 ******************************************************************************/
/**
 * @brief Function to start and control the program.
 */
int main(int, char **) {
	// Essential call to initiate the graphics window
	csci3081::InitGraphics();

	// Initialize default start values for various arena entities
	csci3081::player_params pparams;

	pparams.angle_delta = 10;
	pparams.collision_delta = 1;
	pparams.radius = 20.0;
	pparams.pos = Position(500, 500);
	pparams.color = csci3081::Color(0, 0, 255, 255); /* blue */
	pparams.battery_max_charge = 100;

	csci3081::arena_params aparams;

	aparams.player = pparams;

	aparams.recharge_station.radius = 20.0;
	aparams.recharge_station.pos = {500, 300};
	aparams.recharge_station.color =
		csci3081::Color(0, 128, 128, 255); /* green */

	aparams.home_base.angle_delta = 10;
	aparams.home_base.collision_delta = 1;
	aparams.home_base.radius = 20.0;
	aparams.home_base.pos = {400, 400};
	aparams.home_base.color = csci3081::Color(255, 0, 0, 255); /* red */

	csci3081::robot_params rparam1;

	rparam1.angle_delta = 10;
	rparam1.collision_delta = 1;
	rparam1.radius = 20.0;
	rparam1.pos = Position(700, 175);
	rparam1.starting_pos = Position(700, 175);
	rparam1.color = csci3081::Color(0, 255, 255, 255);

	aparams.robots[0] = rparam1;

	csci3081::robot_params rparam2;

	rparam2.angle_delta = 10;
	rparam2.collision_delta = 1;
	rparam2.radius = 20.0;
	rparam2.pos = Position(800, 400);
	rparam2.starting_pos = Position(800, 400);
	rparam2.color = csci3081::Color(0, 255, 255, 255);

	aparams.robots[1] = rparam2;

	csci3081::robot_params rparam3;

	rparam3.angle_delta = 10;
	rparam3.collision_delta = 1;
	rparam3.radius = 20.0;
	rparam3.pos = Position(175, 700);
	rparam3.starting_pos = Position(175, 700);
	rparam3.color = csci3081::Color(0, 255, 255, 255);

	aparams.robots[2] = rparam3;

	csci3081::robot_params rparam4;

	rparam4.angle_delta = 10;
	rparam4.collision_delta = 1;
	rparam4.radius = 20.0;
	rparam4.pos = Position(320, 277);
	rparam4.starting_pos = Position(320, 277);
	rparam4.color = csci3081::Color(0, 255, 255, 255);

	aparams.robots[3] = rparam4;

	csci3081::robot_params rparam5;

	rparam5.angle_delta = 10;
	rparam5.collision_delta = 1;
	rparam5.radius = 20.0;
	rparam5.pos = Position(570, 630);
	rparam5.starting_pos = Position(570, 630);
	rparam5.color = csci3081::Color(0, 255, 255, 255);

	aparams.robots[4] = rparam5;

	csci3081::superbot_params sparam1;

	sparam1.angle_delta = 10;
	sparam1.collision_delta = 1;
	sparam1.radius = 20.0;
	sparam1.pos = Position(0, 0);
	sparam1.starting_pos = Position(0, 0);
	sparam1.color = csci3081::Color(255, 255, 0, 0);

	aparams.superbots[0] = sparam1;

	csci3081::superbot_params sparam2;

	sparam2.angle_delta = 10;
	sparam2.collision_delta = 1;
	sparam2.radius = 20.0;
	sparam2.pos = Position(0, 0);
	sparam2.starting_pos = Position(0, 0);
	sparam2.color = csci3081::Color(255, 255, 0, 0);

	aparams.superbots[1] = sparam2;

	csci3081::superbot_params sparam3;

	sparam3.angle_delta = 10;
	sparam3.collision_delta = 1;
	sparam3.radius = 20.0;
	sparam3.pos = Position(0, 0);
	sparam3.starting_pos = Position(0, 0);
	sparam3.color = csci3081::Color(255, 255, 0, 0);

	aparams.superbots[2] = sparam3;

	csci3081::superbot_params sparam4;

	sparam4.angle_delta = 10;
	sparam4.collision_delta = 1;
	sparam4.radius = 20.0;
	sparam4.pos = Position(0, 0);
	sparam4.starting_pos = Position(0, 0);
	sparam4.color = csci3081::Color(255, 255, 0, 0);

	aparams.superbots[3] = sparam4;

	csci3081::superbot_params sparam5;

	sparam5.angle_delta = 10;
	sparam5.collision_delta = 1;
	sparam5.radius = 20.0;
	sparam5.pos = Position(0, 0);
	sparam5.starting_pos = Position(0, 0);
	sparam5.color = csci3081::Color(255, 255, 0, 0);

	aparams.superbots[4] = sparam5;

	aparams.obstacles[0].radius = 30.0;
	aparams.obstacles[0].pos = {200, 200};
	aparams.obstacles[0].color = csci3081::Color(255, 255, 255, 255); /* white */

	aparams.obstacles[1].radius = 45.0;
	aparams.obstacles[1].pos = {180, 400};
	aparams.obstacles[1].color = csci3081::Color(255, 255, 255, 255); /* white */

	aparams.obstacles[2].radius = 20.0;
	aparams.obstacles[2].pos = {400, 520};
	aparams.obstacles[2].color = csci3081::Color(255, 255, 255, 255); /* white */

	aparams.obstacles[3].radius = 50.0;
	aparams.obstacles[3].pos = {600, 464};
	aparams.obstacles[3].color = csci3081::Color(255, 255, 255, 255); /* white */

	aparams.obstacles[4].radius = 30.0;
	aparams.obstacles[4].pos = {450, 175};
	aparams.obstacles[4].color = csci3081::Color(255, 255, 255, 255); /* white */

	aparams.n_obstacles = 5;
	aparams.n_robots = 5;
	aparams.n_superbots = 5;
	aparams.x_dim = 1100;
	aparams.y_dim = 740;

	// Start up the graphics (which creates the arena).
	// Run will enter the nanogui::mainloop()
	csci3081::GraphicsArenaViewer *app =
		new csci3081::GraphicsArenaViewer(&aparams);
	app->Run();
	csci3081::ShutdownGraphics();
	return 0;
}
