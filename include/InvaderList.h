//
// Created by Vinu on 9/29/19.
//

#ifndef SPACEINVADERS_INVADERLIST_H
#define SPACEINVADERS_INVADERLIST_H
#include <vector>
#include "Invader.h"
#include <iostream>

class InvaderList : public std::vector<std::shared_ptr<Invader>> {
public:
    enum class Direction{
        Right, Left, Down
    };

    InvaderList(int animationSpeedMs, int leftBound, int rightBound, int lowerBound)
        :mCurrentDirection(Direction::Right), mNextDirectionAfterDown(Direction::Left)
        ,mFrameStart(0), mAnimateSpeedMs(animationSpeedMs)
        ,mLeftBound(leftBound), mRightBound(rightBound), mLowerBound(lowerBound){}

        void Update(int referenceTicks);

        bool Landed();

private:
    Direction mCurrentDirection;
    Direction mNextDirectionAfterDown;
    int mLeftBound, mRightBound, mLowerBound;
    int mAnimateSpeedMs;
    int mFrameStart;

    void SetNextMove();
    void Move();
};

#endif //SPACEINVADERS_INVADERLIST_H
