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

private:
    GameStateManager mGameStateManager; //todo change to unique ptr

    std::vector<std::shared_ptr<Sprite>> mSpriteList;
    std::shared_ptr<Cannon> mCannon;
    std::shared_ptr<Sprite> mProjectile;
    std::shared_ptr<InvaderList> mInvaderList;
    std::shared_ptr<Sprite> mBomb;

    std::vector<std::vector<Rect>> mEnemyAnimations;

    int mScore;
    int mWindowWidth, mWindowHeight, mWindowOffset;
    int mNumRows, mNumEnemiesPerRow;

    void Update(int referenceTicks);

    void Start();
};

#endif //SPACEINVADERS_GAME_H
