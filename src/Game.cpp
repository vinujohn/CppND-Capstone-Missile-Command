//
// Created by Vinu on 9/19/19.
//

#include <iostream>
#include <SDL_timer.h>
#include "Invader.h"
#include "Game.h"
#include <string>

Game::Game(int windowWidth, int windowHeight, int windowOffset)
        : mWindowWidth(windowWidth), mWindowHeight(windowHeight), mWindowOffset(windowOffset) {

    mGameStateManager = std::make_shared<GameStateManager>();

    // TODO remove this to outside of Game using some type of builder pattern.
    mProjectile = std::shared_ptr<Sprite>(new Sprite(std::vector<Rect>{{20, 60, 20, 14}}));
    mCannon = std::shared_ptr<Cannon>(new Cannon(std::vector<Rect>{{20, 42, 20, 18},
                                                                   {0,  42, 20, 18}}, windowWidth, mProjectile, 2));
    mBomb = std::shared_ptr<Sprite>(new Sprite(std::vector<Rect>{{0, 69, 20, 14}}));
    mInvaderList = std::shared_ptr<InvaderList>(
            new InvaderList(500, windowOffset, windowWidth - windowOffset, windowHeight - windowOffset, mBomb));
    mEnemyAnimations = std::vector<std::vector<Rect>>{
            {
                    {0, 0,  20, 14},
                    {20, 0,  20, 14},
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

    mNumEnemiesPerRow = 5;
    mNumRows = 3;
    for (int row = 0; row < mNumRows; row++) {
        for (int col = 0; col < mNumEnemiesPerRow; col++) {
            auto invader = std::shared_ptr<Invader>(new Invader(mEnemyAnimations[row], col % 2));
            mInvaderList->push_back(invader);
        }
    }
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
                    std::cout << "Hit!" << std::endl;
                    mProjectile->Hide();
                    inv->Destroy();
                    mScore += 10;
                    mInvaderList->IncreaseAnimationSpeed();
                }
            }
        }
    }

    if (mInvaderList->Landed()) {
        mCannon->Destroy();
        mGameStateManager->SetState(GameState::Lost);
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
            }
        }
    }

    if (mInvaderList->Destroyed()) {
        mGameStateManager->SetState(GameState::Won);
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
        for (int col = 0; col < mNumEnemiesPerRow; col++) {
            auto invader = (*mInvaderList)[row * mNumEnemiesPerRow + col];
            invader->Move(invader->W() + (2 * col * invader->W()), (mWindowHeight / 5) + (2 * row * invader->H()));
            invader->Display();
        }
    }

    mScore = 0;
}

