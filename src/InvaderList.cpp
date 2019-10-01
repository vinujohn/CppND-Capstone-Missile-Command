//
// Created by Vinu on 9/29/19.
//
#include "InvaderList.h"
#include <random>

void InvaderList::Update(int referenceTicks) {
    if (referenceTicks - mFrameStart > mAnimateSpeedMs) {
        mFrameStart = referenceTicks;

        // remove destroyed invaders from list
        auto it = this->begin();
        while (it != this->end()) {
            auto invader = *it;
            if (invader->Destroyed()) {
                invader = *it;
                invader->Hide();
                it = this->erase(it);
            }else{
                ++it;
            }
        }

        SetNextMove();
        Move();

        DropBomb();
    }
}

void InvaderList::Move() {
    for(auto &inv : *this){
        inv->Animate();
        switch (mCurrentDirection){
            case Direction::Right:
                inv->MoveRight();
                break;
            case Direction::Left:
                inv->MoveLeft();
                break;
            case Direction::Down:
                inv->MoveDown();
                break;
        }
    }
}

bool InvaderList::Landed(){
    for(auto &inv : *this){
        if(!inv->CanMoveDown(mLowerBound)){
            return true;
        }
    }
    return false;
}

void InvaderList::SetNextMove() {

    switch(mCurrentDirection){
        case Direction::Right:
            for(auto &inv : *this){
                if(!inv->CanMoveRight(mRightBound)){
                    mCurrentDirection = Direction::Down;
                    break;
                }
            }
            break;
        case Direction::Left:
            for(auto &inv : *this){
                if(!inv->CanMoveLeft(mLeftBound)){
                    mCurrentDirection = Direction::Down;
                    break;
                }
            }
            break;
        case Direction::Down:
            mCurrentDirection = mNextDirectionAfterDown;
            if (mNextDirectionAfterDown == Direction::Left) {
                mNextDirectionAfterDown = Direction::Right;
            } else {
                mNextDirectionAfterDown = Direction::Left;
            }
            break;
    }

}

void InvaderList::IncreaseAnimationSpeed() {
    mAnimateSpeedMs -= 20;
}

void InvaderList::DropBomb() {
    if(!mBomb->Displayed()){
        // choose random invader
        std::uniform_int_distribution<int> dist(0, this->size() - 1);
        auto randomInvader = (*this)[dist(mRandomEngine)];

        int x = randomInvader->X() - 3 + (randomInvader->W() / 2);
        int y = randomInvader->Y() + randomInvader->H();
        mBomb->Move(x, y);
        mBomb->Display();
    }
}
