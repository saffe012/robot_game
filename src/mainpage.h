/**
 * @file mainpage.h
 *
 * @copyright 2017 3081 Staff, All rights reserved.
 */

/*! \mainpage CSCI3081 Robot Simulator Project
 *
 * \section intro_sec Introduction
 *
 * This software is designed to be a rudimentary robot simulator and visualized
  with a graphics window. As of now, the program is much like a video game in
  which a player controls an entity in the arena and can either win or lose.
  The GraphicsArenaViewer class is where we get the chance to see what the
  code is doing. It interacts with the Arena class the most to show what is
  happening on the virtual arena in real time. The graphics in our program,
  simple_graphics, are only used in the GraphicsArenaViewer class. This would
  make it easy if in the future a programmer would like to use a different
  graphics component. They would only need to update one class. The
  GraphicsArenaViewer is the class that takes in all the mouse input and
  communicates it with the Graphics App. The Arena class controls what is
  actually happening under the hood, in the arena. It interacts with the
  various mobile entities, such as, a player, Robots, and a HomeBase, and
  immobile entity classes like RechargeStation and Obstacle classes to control
  the flow of the game. Many of the movements and functions of the autonomous
  robots and superbots (which inherits from robot) in the arena are controlled
  via different sensors on the robot. These sensors include touch, proximity,
  distress and entity type sensors. Events in the arena cause the sensors to be
  activated then the needed actions are taken by the arena class and sensor
  classes to control the gameplay. The player class takes input from the
  keyboard to control the player’s motions and potentially what other entities
  it interacts with. The motion of the mobile entities (Player, Robot, Superbot,
  HomeBase) are controlled and updated by their respective  MotionHandler and
  MotionBehavior classes.
 *
 * \section install_sec Installation
 *
 * \subsection libsimplegraphics Installing and Using libsimplegraphics
 *
 * etc...
 */
#ifndef SRC_MAINPAGE_H_
#define SRC_MAINPAGE_H_
#endif  // SRC_MAINPAGE_H_
_
