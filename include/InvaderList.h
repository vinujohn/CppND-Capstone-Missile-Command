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
    enum class Direction {
        Right, Left, Down
    };

    InvaderList(
            int animationSpeedMs
            , int increaseAnimateSpeedByMs
            , int numRows
            , int numCols
            , int leftBound
            , int rightBound
            , int lowerBound
            , std::shared_ptr<Sprite> bomb);

    void Update(int referenceTicks);

    bool Landed();

    void IncreaseAnimationSpeed();

    void Reset();

    bool Destroyed();

private:
    Direction mCurrentDirection;
    Direction mNextDirectionAfterDown;
    int mNumRows, mNumCols;
    int mLeftBound, mRightBound, mLowerBound;
    int mStartAnimateSpeedMs, mCurrentAnimateSpeedMs, mIncreaseAnimateSpeedByMs;
    int mFrameStart;
    std::mt19937 mRandomEngine;

    std::shared_ptr<Sprite> mBomb;

    void SetNextMove();

    void Move();

    void DropBomb();
};

#endif //SPACEINVADERS_INVADERLIST_H
