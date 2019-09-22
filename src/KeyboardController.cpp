//
// Created by Vinu on 9/21/19.
//

#include "KeyboardController.h"
#include "SDL.h"

void KeyboardController::HandleInput(GameStateManager &stateManager, Cannon &cannon) {
    SDL_Event e;

    while (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            stateManager.EndGame();
            return;
        }

        switch(e.key.keysym.sym){
            case SDLK_LEFT:
                cannon.MoveLeft();
                break;
            case SDLK_RIGHT:
                cannon.MoveRight();
                break;
            case SDLK_SPACE:
                cannon.Fire();
                break;
        }
    }
}