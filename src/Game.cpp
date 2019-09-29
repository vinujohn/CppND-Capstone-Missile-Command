//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Invader.h"
#include "Game.h"
#include "InvaderList.h"

// TODO figure out how to initialize mCannon cleanly
Game::Game(int windowWidth, int windowHeight, int windowOffset) :mInvaderList(500, windowOffset, windowWidth - windowOffset){
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mWindowOffset = windowOffset;

    // TODO remove this to the outside
    mProjectile = std::shared_ptr<Sprite>(new Sprite(std::vector<Rect>{{20, 60, 20, 14}}));
    mCannon = std::shared_ptr<Cannon>(new Cannon(windowWidth, std::vector<Rect>{{20, 42, 20, 18}}, mProjectile));
    mEnemy = std::shared_ptr<Invader>(new Invader(std::vector<Rect>{{0, 0, 20, 14},{20, 0, 20, 14},{0, 58, 20, 14}}, 0));

    mCannon->Display();
    mEnemy->Display();
    mSpriteList.push_back(mCannon);
    mSpriteList.push_back(mProjectile);

    mInvaderList.push_back(mEnemy);
    mSpriteList.insert(mSpriteList.end(), mInvaderList.begin(), mInvaderList.end());

    score = 0;
}


void Game::Update(int referenceTicks) {
    mInvaderList.Update(referenceTicks);

    if(mProjectile->Displayed()) {
      mProjectile->Move(mProjectile->X(), mProjectile->Y() - 5);

      // went off screen
      if(mProjectile->Y() <= 0){
        mProjectile->Hide();
      }

      // hit enemy
      if(!mEnemy->Destroyed() && mProjectile->X() >= mEnemy->X() && mProjectile->X() <= mEnemy->X() + 20) { //TODO don't hard code
        if(mProjectile->Y() <= mEnemy->Y() + 14){
            std::cout << "HIT!" << std::endl;
            score += 10;
            mProjectile->Hide();
            mEnemy->Destroy();
        }
      }
    }

}

void Game::Run(int delayBetweenFramesMs, Controller &controller, std::function<void()> renderFunc) {
    Uint32 frameStart, frameTime;
    mGameStateManager.SetState(GameState::Started);

    while(mGameStateManager.CurrentGameState() != GameState::Ended){

        frameStart = SDL_GetTicks();

        // game loop
        controller.HandleInput(mGameStateManager, *mCannon);
        Update(frameStart);
        renderFunc(); //TODO temporary

        switch(mGameStateManager.CurrentGameState()){
            case GameState :: Started:
                mEnemy -> Move(mEnemy->W(), mWindowHeight / 5);
                mCannon -> Move(mWindowWidth/2, mWindowHeight - mCannon->H());
                mGameStateManager.SetState((GameState::Running));
                break;
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

