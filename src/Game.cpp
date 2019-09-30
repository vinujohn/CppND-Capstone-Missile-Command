//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Invader.h"
#include "Game.h"

// TODO figure out how to initialize mCannon cleanly
Game::Game(int windowWidth, int windowHeight, int windowOffset) :mInvaderList(500, windowOffset, windowWidth - windowOffset, windowHeight - windowOffset){
    mWindowWidth = windowWidth;
    mWindowHeight = windowHeight;
    mWindowOffset = windowOffset;

    // TODO remove this to the outside
    mProjectile = std::shared_ptr<Sprite>(new Sprite(std::vector<Rect>{{20, 60, 20, 14}}));
    mCannon = std::shared_ptr<Cannon>(new Cannon(windowWidth, std::vector<Rect>{{20, 42, 20, 18}, {0, 42, 20, 18}}, mProjectile));
    auto enemyAnimations = std::vector<std::vector<Rect>>{
        {
            {0, 0, 20, 14},
            {20, 0, 20, 14},
            {0, 58, 20, 14}
        },
        {
            {0, 14, 20, 14},
            {20, 14, 20, 14},
            {0, 58, 20, 14}
        },
        {
            {0, 28, 20, 14},
            {20, 28, 20, 14},
            {0, 58, 20, 14}
        }
    };
    auto numEnemiesPerRow = 5;
    auto invaderY = windowHeight / 5;
    for(int row = 0; row < enemyAnimations.size(); row++){
        for(int col = 0; col < numEnemiesPerRow; col++){
            auto invader =std::shared_ptr<Invader>(new Invader(enemyAnimations[row], col % 2));
            invader->Move(invader->W() + (2*col*invader->W()), invaderY + (2*row*invader->H()));
            invader->Display();
            mInvaderList.push_back(invader);
        }
    }

    mCannon->Display();

    mSpriteList.push_back(mCannon);
    mSpriteList.push_back(mProjectile);

    mSpriteList.insert(mSpriteList.end(), mInvaderList.begin(), mInvaderList.end());

    mScore = 0;
}


void Game::Update(int referenceTicks) {
    mInvaderList.Update(referenceTicks);

    if(mProjectile->Displayed()) {
      mProjectile->Move(mProjectile->X(), mProjectile->Y() - 5);

      // went off screen
      if(mProjectile->Y() <= 0){
        mProjectile->Hide();
      }

      for(auto &inv:mInvaderList){
          if(mProjectile->Collided(*inv)){
              std::cout << "Hit!" << std::endl;
              mProjectile->Hide();
              inv->Destroy();
              mScore += 10;
          }
      }
    }

    if(mInvaderList.Landed()){
        mCannon->Destroy();
        mGameStateManager.EndGame();
    }
}

void Game::Run(int delayBetweenFramesMs, Controller &controller, Renderer &renderer) {
    Uint32 frameStart, frameTime;
    mGameStateManager.SetState(GameState::Started);

    while(mGameStateManager.CurrentGameState() != GameState::Exited){

        frameStart = SDL_GetTicks();

        // game loop
        controller.HandleInput(mGameStateManager, *mCannon);

        switch(mGameStateManager.CurrentGameState()){
            case GameState :: Started:
                mCannon -> Move(mWindowWidth/2, mWindowHeight - mCannon->H());
                mGameStateManager.SetState((GameState::Running));
                break;
            case GameState::Running:
                Update(frameStart);
                renderer.Render(mSpriteList);
                renderer.UpdateScore(mScore);
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

