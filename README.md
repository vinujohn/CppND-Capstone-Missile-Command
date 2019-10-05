# CPPND: Space Invaders

## Description
Space Invaders is a classical 2D game which was introduced in the late 70's.  The game consists of an array of invaders
who are trying to make their way to the bottom of the screen.  The player, controls a cannon which moves left or right
and can shoot one projectile at a time at the invaders to destroy them.  The invaders can also collectively drop one 
bomb at a time trying to destroy the player's cannon.  The game ends when either the player's cannon is destroyed by 
a bomb, the invaders have made it to the bottom of the screen, or the player has successfully destroyed all invaders.

## Implementation
<p>
<img align="right" src="markdown/files.png">
The game works using the SDL2 game engine to render a bunch of different sprites/assets to the screen at a particular 
framerate while handling user input for the player.  The project itself is composed of the following classes.

* Major Components
    * Game
        * Manages the state of the game
        * Runs the game loop. (handle input, update game, render to screen)
        * Handles interactions between different assets in the game like making sure an invader is destroyed after it
        is hit by a projectile
    * Renderer
        * Renders a frame onto the screen
        * Holds all SDL2 rendering objects
        * Is used by the Game class to render assets to the screen, display message boxes, and update the title bar
    * Controller/KeyboardController
        * Controls the Cannon object by setting its state so that it can move left or right and fire a projectile based
        on keyboard input.
        * KeyboardController inherits from Controller.  Another controller could also be used like a 
        JoystickController and just plugged into the game.
        * Listens for the SDL2 Exit game event when the user tries to leave the game by closing the window.
        * Used by the Game class to be called on every time input is needed.
* Minor Components
    * Sprite
        * Every asset that can be drawn on the screen inherits from this class or uses this class directly.
        * Holds common attributes for every sprite including sprite coordinates, animations, and common behavior like
        Display() and Hide()
    * Cannon
        * Controlled by the player
        * Can move left or right and fire a projectile
        * Can be destroyed by invader bombs or if an invader has reach the bottom of the screen
    * Invader/InvaderList
        * Invader made up of multiple animations including a common "destroyed" animation
        * InvaderList derives from a vector of Invaders and holds state information common to all invaders like the
        current direction that all invaders should be moving towards
    * GameState
        * Holds game state so that multiple components can query this state or set it
        * Used by the KeyboardController to exit the game if the user closes the game window
        * States include Started, Running, Won, Lost, ExitCalled
        * Friend class to the Game itself
</p>

---
## Dependencies for Running Locally
* cmake >= 3.7
  * All OSes: [click here for installation instructions](https://cmake.org/install/)
* make >= 4.1 (Linux, Mac), 3.81 (Windows)
  * Linux: make is installed by default on most Linux distros
  * Mac: [install Xcode command line tools to get make](https://developer.apple.com/xcode/features/)
  * Windows: [Click here for installation instructions](http://gnuwin32.sourceforge.net/packages/make.htm)
* SDL2 >= 2.0
  * All installation instructions can be found [here](https://wiki.libsdl.org/Installation)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* SDL2 Image >= 2.0
  * All installation instructions can be found [here](https://www.libsdl.org/projects/SDL_image/)
  * Note that for Linux, an `apt` or `apt-get` installation is preferred to building from source.
* gcc/g++ >= 5.4
  * Linux: gcc / g++ is installed by default on most Linux distros
  * Mac: same deal as make - [install Xcode command line tools](https://developer.apple.com/xcode/features/)
  * Windows: recommend using [MinGW](http://www.mingw.org/)

## Basic Build Instructions

1. Clone this repo.
2. Make a build directory in the top level directory: `mkdir build && cd build`
3. Compile: `cmake .. && make`
4. Run it: `./SpaceInvaders`.
