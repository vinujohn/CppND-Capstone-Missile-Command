//
// Created by Vinu on 9/29/19.
//

#ifndef SPACEINVADERS_INVADERLIST_H
#define SPACEINVADERS_INVADERLIST_H
#include <vector>
#include "Invader.h"
#include <iostream>
#include <random>

class InvaderList : public std::vector<std::shared_ptr<Invader>> {
public:
    enum class Direction{
        Right, Left, Down
    };

    InvaderList(int animationSpeedMs, int leftBound, int rightBound, int lowerBound, std::shared_ptr<Sprite> bomb)
        : mCurrentDirection(Direction::Right), mNextDirectionAfterDown(Direction::Left)
        , mFrameStart(0), mBomb(bomb), mStartAnimateSpeedMs(animationSpeedMs), mCurrentAnimateSpeedMs(animationSpeedMs)
        , mLeftBound(leftBound), mRightBound(rightBound), mLowerBound(lowerBound){

        std::random_device rd;
        mRandomEngine = std::mt19937{rd()};
    }

        void Update(int referenceTicks);

        bool Landed();

        void IncreaseAnimationSpeed();

        void Reset();

        bool Destroyed();

private:
    Direction mCurrentDirection;
    Direction mNextDirectionAfterDown;
    int mLeftBound, mRightBound, mLowerBound;
    int mStartAnimateSpeedMs;
    int mCurrentAnimateSpeedMs;
    int mFrameStart;
    std::mt19937 mRandomEngine;

    std::shared_ptr<Sprite> mBomb;

    void SetNextMove();
    void Move();
    void DropBomb();
};

#endif //SPACEINVADERS_INVADERLIST_H
