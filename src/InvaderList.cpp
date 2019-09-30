//
// Created by Vinu on 9/29/19.
//
#include "InvaderList.h"

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
