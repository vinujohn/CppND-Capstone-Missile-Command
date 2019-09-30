//
// Created by Vinu on 9/21/19.
//

#include "KeyboardController.h"
#include "SDL.h"

void KeyboardController::HandleInput(GameStateManager &stateManager, Cannon &cannon) {
    SDL_Event e;
    if (SDL_PollEvent(&e)) {
        if (e.type == SDL_QUIT) {
            stateManager.ExitGame();
            return;
        }
    }

    const Uint8* currentKeyStates = SDL_GetKeyboardState( nullptr );

    if(currentKeyStates[SDL_SCANCODE_RIGHT]){
        cannon.MoveRight();
    }
    if(currentKeyStates[SDL_SCANCODE_LEFT]){
        cannon.MoveLeft();
    }
    if(currentKeyStates[SDL_SCANCODE_SPACE]){
        cannon.Fire();
    }
}