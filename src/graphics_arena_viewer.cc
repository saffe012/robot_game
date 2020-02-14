/**
 * @file graphics_arena_viewer.cc
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*******************************************************************************
 * Includes
 ******************************************************************************/
#include "src/graphics_arena_viewer.h"
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

#include "src/robot.h"
#include "src/home_base.h"
#include "src/obstacle.h"
#include "src/arena_params.h"
#include "src/event_keypress.h"

/*******************************************************************************
 * Namespaces
 ******************************************************************************/
NAMESPACE_BEGIN(csci3081);

/*******************************************************************************
 * Constructors/Destructor
 ******************************************************************************/
/**
 * @brief GraphicsArenaViewer constructor
 * @param params Parameters of the Arena class for GraphicsArenaViewer
 */
GraphicsArenaViewer::GraphicsArenaViewer(const struct arena_params* const params) :
	csci3081::GraphicsApp(1100, 900, "Robot Simulation"), arena_(new Arena(params)),
	paused_(false), pause_btn_(nullptr), battery_btn_(nullptr), last_dt(-1) {

	nanogui::FormHelper *gui = new nanogui::FormHelper(this);
	nanogui::ref<nanogui::Window> window = gui->addWindow(Eigen::Vector2i(935, 760),
	                                                      "Simulation Controls");
	gui->addButton("Restart", std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
	pause_btn_ = gui->addButton("Pause", std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

	battery_btn_ = gui->addButton("Battery:", std::bind(&GraphicsArenaViewer::OnBatteryBtnPressed, this));

	last_dt = 0;
	performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/
/**
 * @brief Informs the arena of the new time, so that it can update.
 * This is the primary driver for state change in the arena.
 * It will be called at each iteration of nanogui::mainloop()
 *
 * @param dt The # of timesteps that has elapsed since the last time
 *   position/velocity were updated.
 */
void GraphicsArenaViewer::UpdateSimulation(double dt) {
	if (!paused_) {
		int game_status;
		if ((last_dt + dt) > .05) {
			game_status = arena_->AdvanceTime();
			std::string battery = std::to_string(arena_->get_player_battery_level());
			battery_btn_->setCaption(battery);
			last_dt = 0;
		}
		else {
			last_dt += dt;
		}

		if (game_status == 0) {
			pause_btn_->setCaption("You Lose :(");
			paused_ = true;
		}
		else if (game_status == 1) {
			pause_btn_->setCaption("You win :)");
			paused_ = true;
		}
	}
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
/**
 * @brief Handle the user pressing the restart button on the GUI.
 */
void GraphicsArenaViewer::OnRestartBtnPressed() {
	arena_->Reset();
	pause_btn_->setCaption("Play");
	paused_ = true;
}

/**
 * @brief Function that does nothing. Used to Bind battery presenter button to
 */
void GraphicsArenaViewer::OnBatteryBtnPressed() {
}

/**
 * @brief Handle the user pressing the pause button on the GUI.
 */
void GraphicsArenaViewer::OnPauseBtnPressed() {
	paused_ = !paused_;
	if (paused_) {
		pause_btn_->setCaption("Play");
	}
	else {
		pause_btn_->setCaption("Pause");
	}
}

/**
 * @brief Called each time the mouse moves on the screen within the GUI
 * window.
 *
 * Origin is at the lower left of the window.
 *
 * @param x X position of the cursor.
 * @param y Y position of the cursor.
 */
void GraphicsArenaViewer::OnMouseMove(__unused int x, __unused int y) {
	// std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

/**
 * @brief Called each time the left mouse button is clicked.
 *
 * Origin is at the lower left of the window.
 *
 * @param x The X position of the click.
 * @param y The Y position of the click.
 */
void GraphicsArenaViewer::OnLeftMouseDown(__unused int x, __unused int y) {
	// std::cout << "Left mouse button DOWN (" << x << ", " << y << ")"
	// << std::endl;
}

/**
 * @brief Called each time the left mouse button is released.
 *
 * Origin is at the lower left of the window.
 *
 * @param x The X position of the release.
 * @param y The Y position of the release.
 */
void GraphicsArenaViewer::OnLeftMouseUp(__unused int x, __unused int y) {
	// std::cout << "Left mouse button UP (" << x << ", " << y << ")"
	// << std::endl;
}

/**
 * @brief Called each time the right mouse button is clicked.
 *
 * Origin is at the lower left of the window.
 *
 * @param x The X position of the click.
 * @param y The Y position of the click.
 */
void GraphicsArenaViewer::OnRightMouseDown(__unused int x, __unused int y) {
	// std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

/**
 * @brief Called each time the right mouse button is released.
 *
 * Origin is at the lower left of the window.
 *
 * @param x The X position of the release.
 * @param y The Y position of the release.
 */
void GraphicsArenaViewer::OnRightMouseUp(__unused int x, __unused int y) {
	// std::cout << "Right mouse button UP (" << x << ", " << y << ")"
	// << std::endl;
}

/**
 * @brief Called each time a character key is pressed.
 *
 * @param c Character representing a key that was pressed.
 * @param modifiers Any modifier keys that were also pressed.
 */
void GraphicsArenaViewer::OnKeyDown(const __unused char *c,
                                    __unused int modifiers) {
	// std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

/**
 * @brief Called each time a character key is released.
 *
 * @param c Character representing a key that was released.
 * @param modifiers Any modifier keys that were held with the key.
 */
void GraphicsArenaViewer::OnKeyUp(const __unused char *c,
                                  __unused int modifiers) {
	// std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

/**
 * @brief Called each time a special (non-alphabetic) key is pressed.
 *
 * @param key The key that was pressed.
 * @param scancode The scancode corresponding to the key.
 * @param modifiers Any modifiers that were also pressed.
 */
void GraphicsArenaViewer::OnSpecialKeyDown(int key, __unused int scancode,
                                           __unused int modifiers) {
	EventKeypress e(key);
	arena_->Accept(key);
	// std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
	//          << " modifiers=" << modifiers << std::endl;
}

/**
 * @brief Called each time a special (non-alphabetic) key is released.
 *
 * @param key The key that was released.
 * @param scancode The scancode corresponding to the key.
 * @param modifiers Any modifiers that were also pressed.
 */
void GraphicsArenaViewer::OnSpecialKeyUp(__unused int key,
                                         __unused int scancode, __unused int modifiers) {
	// std::cout << "Special Key UP key=" << key << " scancode=" << scancode
	//          << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
/**
 * @brief Draw a player using nanogui.
 *
 * This function requires an active nanovg drawing context (ctx), so it should
 * probably only be called from with \ref DrawUsingNanoVG().
 *
 * @param ctx The nanogui context.
 * @param robot The player handle.
 */
void GraphicsArenaViewer::DrawPlayer(NVGcontext *ctx,
                                     const Player* const player) {
	// translate and rotate all graphics calls that follow so that they are
	// centered, at the position and heading for this robot
	nvgSave(ctx);
	nvgTranslate(ctx, player->get_pos().x(), player->get_pos().y());
	nvgRotate(ctx, player->get_heading_angle());

	// robot's circle
	nvgBeginPath(ctx);
	nvgCircle(ctx, 0.0, 0.0, player->get_radius());
	nvgFillColor(ctx, nvgRGBA(static_cast<int>(player->get_color().r),
	                          static_cast<int>(player->get_color().g),
	                          static_cast<int>(player->get_color().b),
	                          255));
	nvgFill(ctx);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgStroke(ctx);

	// robot id text label
	nvgSave(ctx);
	nvgRotate(ctx, M_PI / 2.0);
	nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgText(ctx, 0.0, 10.0, player->get_name().c_str(), NULL);
	nvgRestore(ctx);

	nvgRestore(ctx);
}

/**
 * @brief Draw a robot using nanogui.
 *
 * This function requires an active nanovg drawing context (ctx), so it should
 * probably only be called from with \ref DrawUsingNanoVG().
 *
 * @param ctx The nanogui context.
 * @param robot The robot handle.
 */
void GraphicsArenaViewer::DrawRobot(NVGcontext *ctx, const Robot* const robot) {
	// translate and rotate all graphics calls that follow so that they are
	// centered, at the position and heading for this robot
	nvgSave(ctx);
	nvgTranslate(ctx, robot->get_pos().x(), robot->get_pos().y());
	nvgRotate(ctx, robot->get_heading_angle());

	// robot's circle
	nvgBeginPath(ctx);
	nvgCircle(ctx, 0.0, 0.0, robot->get_radius());
	nvgFillColor(ctx, nvgRGBA(static_cast<int>(robot->get_color().r),
	                          static_cast<int>(robot->get_color().g),
	                          static_cast<int>(robot->get_color().b),
	                          255));
	nvgFill(ctx);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgStroke(ctx);

	// robot id text label
	nvgSave(ctx);
	nvgRotate(ctx, M_PI / 2.0);
	nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgText(ctx, 0.0, 10.0, robot->get_name().c_str(), NULL);
	nvgRestore(ctx);

	nvgRestore(ctx);
}

/**
 * @brief Draw an obstacle in the arena using nanogui.
 *
 * This function requires an active nanovg drawing context (ctx), so it should
 * probably only be called from with \ref DrawUsingNanoVG().
 *
 * @param ctx The nanogui context.
 * @param obstacle The obstacle handle.
 */
void GraphicsArenaViewer::DrawObstacle(NVGcontext *ctx,
                                       const Obstacle* const obstacle) {
	nvgBeginPath(ctx);
	nvgCircle(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
	          obstacle->get_radius());
	nvgFillColor(ctx, nvgRGBA(static_cast<int>(obstacle->get_color().r),
	                          static_cast<int>(obstacle->get_color().g),
	                          static_cast<int>(obstacle->get_color().b),
	                          255));
	nvgFill(ctx);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgStroke(ctx);

	nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgText(ctx, obstacle->get_pos().x(), obstacle->get_pos().y(),
	        obstacle->get_name().c_str(), NULL);
}

/**
 * @brief Draw the home base using nanogui.
 *
 * @param ctx The nanogui context.
 * @param home The home base handle.
 */
void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx, const HomeBase* const home) {
	nvgBeginPath(ctx);
	nvgCircle(ctx, home->get_pos().x(), home->get_pos().y(), home->get_radius());
	nvgFillColor(ctx, nvgRGBA(static_cast<int>(home->get_color().r),
	                          static_cast<int>(home->get_color().g),
	                          static_cast<int>(home->get_color().b),
	                          255));
	nvgFill(ctx);
	nvgStrokeColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgStroke(ctx);

	nvgFillColor(ctx, nvgRGBA(0, 0, 0, 255));
	nvgText(ctx, home->get_pos().x(), home->get_pos().y(),
	        home->get_name().c_str(), NULL);
}

/**
 * @brief Draw the arena with all robots, obstacles using nanogui.
 *
 * This is the primary driver for drawing all entities in the arena.  It is
 * called at each iteration of \ref nanogui::mainloop().
 *
 * @param ctx Context for nanogui.
 */
void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
	// initialize text rendering settings
	nvgFontSize(ctx, 18.0f);
	nvgFontFace(ctx, "sans-bold");
	nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

	std::vector<Obstacle*> obstacles = arena_->obstacles();
	std::vector<Robot*> robots = arena_->robots();
	for (size_t i = 0; i < obstacles.size(); i++) {
		DrawObstacle(ctx, obstacles[i]);
	}

	for (size_t i = 0; i < robots.size(); i++) {
		DrawRobot(ctx, robots[i]);
	}

	DrawPlayer(ctx, arena_->player());
	DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
