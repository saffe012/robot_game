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
GraphicsArenaViewer::GraphicsArenaViewer(
  const struct arena_params* const params)
    : csci3081::GraphicsApp(1100, 900, "Robot Simulation"),
      arena_(new Arena(params)),
      paused_(false),
      pause_btn_(nullptr),
      battery_btn_(nullptr),
      last_dt(-1) {
  nanogui::FormHelper *gui = new nanogui::FormHelper(this);
  nanogui::ref<nanogui::Window> window =
    gui->addWindow(Eigen::Vector2i(935, 760),
                                                       "Simulation Controls");
  gui->addButton("Restart",
    std::bind(&GraphicsArenaViewer::OnRestartBtnPressed, this));
  pause_btn_ = gui->addButton("Pause",
    std::bind(&GraphicsArenaViewer::OnPauseBtnPressed, this));

  battery_btn_ = gui->addButton("Battery:",
    std::bind(&GraphicsArenaViewer::OnBatteryBtnPressed, this));

  last_dt = 0;
  performLayout();
}

/*******************************************************************************
 * Member Functions
 ******************************************************************************/

// This is the primary driver for state change in the arena.
// It will be called at each iteration of nanogui::mainloop()
void GraphicsArenaViewer::UpdateSimulation(double dt) {
  if (!paused_) {
    int game_status;
    if ((last_dt + dt) > .05) {
      game_status = arena_->AdvanceTime();
      std::string battery = std::to_string(arena_->get_player_battery_level());
      battery_btn_->setCaption(battery);
      last_dt = 0;
    } else {
      last_dt += dt;
    }

    if (game_status == 0) {
      pause_btn_->setCaption("You Lose :(");
      paused_ = true;
    } else if (game_status == 1) {
      pause_btn_->setCaption("You win :)");
      paused_ = true;
    }
  }
}

/*******************************************************************************
 * Handlers for User Keyboard and Mouse Events
 ******************************************************************************/
void GraphicsArenaViewer::OnRestartBtnPressed() {
  arena_->Reset();
  pause_btn_->setCaption("Play");
  paused_ = true;
}

void GraphicsArenaViewer::OnBatteryBtnPressed() {
}

void GraphicsArenaViewer::OnPauseBtnPressed() {
  paused_ = !paused_;
  if (paused_) {
    pause_btn_->setCaption("Play");
  } else {
    pause_btn_->setCaption("Pause");
  }
}

void GraphicsArenaViewer::OnMouseMove(__unused int x, __unused int y) {
  // std::cout << "Mouse moved to (" << x << ", " << y << ")" << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseDown(__unused int x, __unused int y) {
  // std::cout << "Left mouse button DOWN (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnLeftMouseUp(__unused int x, __unused int y) {
  // std::cout << "Left mouse button UP (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnRightMouseDown(__unused int x, __unused int y) {
  // std::cout << "Right mouse button DOWN (" << x << ", " << y << ")\n";
}

void GraphicsArenaViewer::OnRightMouseUp(__unused int x, __unused int y) {
  // std::cout << "Right mouse button UP (" << x << ", " << y << ")"
  // << std::endl;
}

void GraphicsArenaViewer::OnKeyDown(const __unused char *c,
  __unused int modifiers) {
  // std::cout << "Key DOWN (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnKeyUp(const __unused char *c,
  __unused int modifiers) {
  // std::cout << "Key UP (" << c << ") modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyDown(int key, __unused int scancode,
  __unused int modifiers) {
  EventKeypress e(key);
  arena_->Accept(key);
  // std::cout << "Special Key DOWN key=" << key << " scancode=" << scancode
  //          << " modifiers=" << modifiers << std::endl;
}

void GraphicsArenaViewer::OnSpecialKeyUp(__unused int key,
  __unused int scancode, __unused int modifiers) {
  // std::cout << "Special Key UP key=" << key << " scancode=" << scancode
  //          << " modifiers=" << modifiers << std::endl;
}

/*******************************************************************************
 * Drawing of Entities in Arena
 ******************************************************************************/
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

void GraphicsArenaViewer::DrawHomeBase(NVGcontext *ctx,
                               const HomeBase* const home) {
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

void GraphicsArenaViewer::DrawUsingNanoVG(NVGcontext *ctx) {
  // initialize text rendering settings
  nvgFontSize(ctx, 18.0f);
  nvgFontFace(ctx, "sans-bold");
  nvgTextAlign(ctx, NVG_ALIGN_CENTER | NVG_ALIGN_MIDDLE);

  std::vector<Obstacle*> obstacles = arena_->obstacles();
  std::vector<Robot*> robots = arena_->robots();
  for (size_t i = 0; i < obstacles.size(); i++) {
    DrawObstacle(ctx, obstacles[i]);
  } /* for(i..) */

  for (size_t i = 0; i < robots.size(); i++) {
    DrawRobot(ctx, robots[i]);
  } /* for(i..) */

  DrawPlayer(ctx, arena_->player());
  DrawHomeBase(ctx, arena_->home_base());
}

NAMESPACE_END(csci3081);
