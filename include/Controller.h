//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_CONTROLLER_H
#define SPACEINVADERS_CONTROLLER_H

#include "Cannon.h"
#include "GameState.h"

class Controller {
public:
    virtual void HandleInput(GameStateManager &, Cannon &) const = 0;
};

#endif //SPACEINVADERS_CONTROLLER_H
