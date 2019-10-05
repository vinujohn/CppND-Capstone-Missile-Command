//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Invader.h"
#include "Game.h"
#include <string>

Game::Game(int windowWidth
            , int windowHeight
            , int windowOffset
            , std::shared_ptr<Sprite> projectile
            , std::shared_ptr<Cannon> cannon
            , std::shared_ptr<Sprite> bomb
            , std::shared_ptr<InvaderList> invaderList
            , int numRows
            , int numInvadersPerRow)
        : mWindowWidth(windowWidth)
        , mWindowHeight(windowHeight)
        , mWindowOffset(windowOffset)
        , mProjectile(projectile)
        , mCannon(cannon)
        , mBomb(bomb)
        , mInvaderList(invaderList)
        , mNumRows(numRows)
        , mNumInvadersPerRow(numInvadersPerRow){

    mGameStateManager = std::make_shared<GameStateManager>();

    mSpriteList.insert(mSpriteList.end(), mInvaderList->begin(), mInvaderList->end());
    mSpriteList.push_back(mCannon);
    mSpriteList.push_back(mProjectile);
    mSpriteList.push_back(mBomb);
}

void Game::Update(int referenceTicks) {
    mInvaderList->Update(referenceTicks);

    if (mProjectile->Displayed()) {
        mProjectile->Move(mProjectile->X(), mProjectile->Y() - 5);

        // went off screen
        if (mProjectile->Y() <= 0) {
            mProjectile->Hide();
        } else {
            for (auto &inv:*mInvaderList) {
                if (!(*inv).Destroyed() && mProjectile->Collided(*inv)) {
                    mProjectile->Hide();
                    inv->Destroy();
                    mScore += 10;
                    mInvaderList->IncreaseAnimationSpeed();
                    std::cout << "Enemy Destroyed" << std::endl;
                }
            }
        }
    }

    if (mInvaderList->Landed()) {
        mCannon->Destroy();
        mGameStateManager->SetState(GameState::Lost);
        std::cout << "Invasion Successful" << std::endl;
    }

    if (mBomb->Displayed()) {
        mBomb->Move(mBomb->X(), mBomb->Y() + 3);

        // went off screen
        if (mBomb->Y() >= mWindowHeight) {
            mBomb->Hide();
        } else { // enemy bomb hit cannon
            if (mBomb->Collided(*mCannon)) {
                mCannon->Destroy();
                mBomb->Hide();
                mGameStateManager->SetState(GameState::Lost);
                std::cout << "Cannon Destroyed" << std::endl;
            }
        }
    }

    if (mInvaderList->Destroyed()) {
        mGameStateManager->SetState(GameState::Won);
        std::cout << "All Enemies Destroyed" << std::endl;
    }
}

void Game::Run(int delayBetweenFramesMs, Controller &controller, Renderer &renderer) {
    Uint32 frameStart, frameTime;
    mGameStateManager->SetState(GameState::Started);

    while (!mGameStateManager->ShouldExitNow()) {

        frameStart = SDL_GetTicks();

        // game loop
        controller.HandleInput(*mGameStateManager, *mCannon);

        MessageBoxOutput choice = MessageBoxOutput::Unknown;
        switch (mGameStateManager->GetState()) {
            case GameState::Started:
                Start();
                mGameStateManager->SetState((GameState::Running));
                break;
            case GameState::Running:
                Update(frameStart);
                renderer.Render(mSpriteList);
                renderer.UpdateScore(mScore);
                break;
            case GameState::Won:
                choice = renderer.DisplayEndGameMessage("You Won!", mScore);
                break;
            case GameState::Lost:
                choice = renderer.DisplayEndGameMessage("You Lose!", mScore);
                break;
            case GameState::ExitCalled:
                mGameStateManager->mExitNow = true;
                break;
        }

        if (choice == MessageBoxOutput::Yes) {
            mGameStateManager->SetState(GameState::Started);
        } else if (choice == MessageBoxOutput::Exit) {
            mGameStateManager->ExitGame();
        }

        frameTime = SDL_GetTicks() - frameStart;
        if (frameTime < delayBetweenFramesMs) {
            SDL_Delay((delayBetweenFramesMs - (int)frameTime));
        }
    }

    std::cout << "game has ended" << std::endl;
}

void Game::Start() {
    mCannon->Move(mWindowWidth / 2, mWindowHeight - mCannon->H());
    mCannon->Reset();
    mCannon->Display();
    mProjectile->Hide();
    mBomb->Hide();

    mInvaderList->Reset();
    for (int row = 0; row < mNumRows; row++) {
        for (int col = 0; col < mNumInvadersPerRow; col++) {
            auto invader = (*mInvaderList)[row * mNumInvadersPerRow + col];
            invader->Move(invader->W() + (2 * col * invader->W()), (mWindowHeight / 5) + (2 * row * invader->H()));
            invader->Display();
        }
    }

    mScore = 0;
}

