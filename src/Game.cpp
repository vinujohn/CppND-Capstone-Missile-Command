//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Game.h"

// TODO figure out how to initialize mCannon cleanly
Game::Game(int windowWidth, int windowHeight, int windowOffset) {
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mWindowOffset = windowOffset;

    mCannon = std::unique_ptr<Cannon>(new Cannon(std::vector<Rect>{{20, 42, 20, 18}},
            std::vector<Rect>{{20, 60, 20, 14}}));

    firing = false;
    score = 0;
}

void Game::Start() {
    running = true;
    Ship = Asset{"ship", mWindowWidth / 2, mWindowHeight - mWindowOffset};
    Enemy = Asset{"enemy", mWindowOffset, mWindowHeight / 5};
    Enemy.movingLeft = false;
}

void Game::MoveRight() {
    if(Ship.x < (mWindowWidth - mWindowOffset)){
        Ship.x += moveShipBy;
    }
}

void Game::MoveLeft() {
    if(Ship.x > 0){
        Ship.x -= moveShipBy;
    }
}

void Game::Fire() {
    if(!IsFiring()){
        std::cout << "firing..." << std::endl;
        firing = true;
        Projectile = Asset{"projectile", Ship.x + 8, Ship.y-1}; //TODO don't hardcode
    }
}

void Game::Update() {
    auto now = SDL_GetTicks();
    if(now - mframeStart > enemyAnimationMs){ //TODO: get rid of SDL here
        Enemy.currentFrame = (Enemy.currentFrame + 1) % 2;
        mframeStart = now;
        if(!Enemy.destroyed) {
            if (Enemy.movingLeft == false && Enemy.x + 20 < (mWindowWidth - mWindowOffset)) {
                Enemy.x = Enemy.x + 20;
            } else if (Enemy.movingLeft == false) {
                Enemy.y += 14;
                Enemy.movingLeft = true;
            } else if (Enemy.movingLeft && Enemy.x - 20 > 0) {
                Enemy.x -= 20;
            } else {
                Enemy.y += 14;
                Enemy.movingLeft = false;
            }
        }
    }

    if(IsFiring()){
        Projectile.y -= 5;
        if(Projectile.y <= 0){
            firing=false;
            Projectile.y = -1;
        }


        if(!Enemy.destroyed && Projectile.x >= Enemy.x && Projectile.x <= Enemy.x + 20) { //TODO don't hard code
            if(Projectile.y <= Enemy.y + 14){
                std::cout << "HIT!" << std::endl;
                Enemy.destroyed = true;
                score += 10;
            }
        }
    }
}

void Game::Run(int delayBetweenFramesMs, Controller &controller, void renderFunc()) {
    Uint32 frameStart, frameTime;
    mGameStateManager.SetState(GameState::Running);

    while(mGameStateManager.CurrentGameState() != GameState::Ended){

        frameStart = SDL_GetTicks();

        // game loop
        controller.HandleInput(mGameStateManager, *mCannon);
        Update();
        renderFunc(); //TODO temporary

        switch(mGameStateManager.CurrentGameState()){
            case GameState :: Ending:
                mGameStateManager.SetState(GameState::Ended);
                break;
        }

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < delayBetweenFramesMs)
        {
            SDL_Delay((int)(delayBetweenFramesMs - frameTime));
        }
    }

    std::cout << "game has ended" << std::endl;
}

