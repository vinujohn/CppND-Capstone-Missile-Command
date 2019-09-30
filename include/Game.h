//
// Created by Vinu on 9/19/19.
//

#ifndef SPACEINVADERS_GAME_H
#define SPACEINVADERS_GAME_H

#include <string>
#include <chrono>
#include <SDL_types.h>
#include "GameState.h"
#include "Controller.h"
#include "Cannon.h"
#include "Renderer.h"
#include "Invader.h"
#include "InvaderList.h"

class Game {
public:
    Game(int windowWidth, int windowHeight, int windowOffset);

    void Run(int delayBetweenFramesMs, Controller&, Renderer&);

    void Update(int referenceTicks);

private:
    GameStateManager mGameStateManager; //todo change to unique ptr

    std::vector<std::shared_ptr<Sprite>> mSpriteList;
    std::shared_ptr<Cannon> mCannon;
    std::shared_ptr<Sprite> mProjectile;
    InvaderList mInvaderList;

    int mScore;
    int mWindowWidth, mWindowHeight, mWindowOffset;
};

#endif //SPACEINVADERS_GAME_H
