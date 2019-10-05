//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_KEYBOARDCONTROLLER_H
#define SPACEINVADERS_KEYBOARDCONTROLLER_H

#include "Controller.h"

class KeyboardController : public Controller {

public:
    void HandleInput(GameStateManager &, Cannon &) override;
};

#endif //SPACEINVADERS_KEYBOARDCONTROLLER_H
