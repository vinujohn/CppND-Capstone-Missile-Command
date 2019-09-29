//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Invader.h"
#include "Game.h"
#include "InvaderList.h"

// TODO figure out how to initialize mCannon cleanly
Game::Game(int windowWidth, int windowHeight, int windowOffset) {
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
    mSpriteList.push_back(mEnemy);

    score = 0;
}


void Game::Update(int referenceTicks) {
    if(referenceTicks - mframeStart > enemyAnimationMs){
        mframeStart = referenceTicks;
        if(!mEnemy->mDestroyed) {
            mEnemy->Animate();
            if (mEnemy -> mMovingLeft == false && mEnemy->X() + 20 < (mWindowWidth - mWindowOffset)) {
                mEnemy->Move(mEnemy->X() + 20, mEnemy->Y());
            } else if (mEnemy->mMovingLeft == false) {
                mEnemy->Move(mEnemy->X(), mEnemy->Y() + 14);
                mEnemy->mMovingLeft = true;
            } else if (mEnemy->mMovingLeft && mEnemy->X() - 20 > 0) {
                mEnemy->Move(mEnemy->X() - 20, mEnemy->Y());
            } else {
                mEnemy->Move(mEnemy->X(), mEnemy->Y() + 14);
                mEnemy->mMovingLeft = false;
            }
        }
    }

    if(mProjectile->Displayed()) {
      mProjectile->Move(mProjectile->X(), mProjectile->Y() - 5);

      // went off screen
      if(mProjectile->Y() <= 0){
        mProjectile->Hide();
      }

      // hit enemy
      if(!mEnemy->mDestroyed && mProjectile->X() >= mEnemy->X() && mProjectile->X() <= mEnemy->X() + 20) { //TODO don't hard code
        if(mProjectile->Y() <= mEnemy->Y() + 14){
            std::cout << "HIT!" << std::endl;
            mEnemy->mDestroyed = true;
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

