//
// Created by Vinu on 9/29/19.
//

#ifndef SPACEINVADERS_INVADERLIST_H
#define SPACEINVADERS_INVADERLIST_H
#include <vector>
#include "Invader.h"

class InvaderList : public std::vector<std::shared_ptr<Invader>> {
public:
    enum class Direction{
        Right, Left, Down
    };

    InvaderList(int animationSpeedMs, int leftBound, int rightBound)
        :mCurrentDirection(Direction::Right), mNextDirectionAfterDown(Direction::Left)
        ,mFrameStart(0), mAnimateSpeedMs(animationSpeedMs)
        ,mLeftBound(leftBound), mRightBound(rightBound){}

    void Update(int referenceTicks){
        if(referenceTicks - mFrameStart > mAnimateSpeedMs){
            mFrameStart = referenceTicks;

            auto it = this->begin();
            while(it != this->end()){
                // remove destroyed invaders from list
                auto invader = *it;
                if(invader->Destroyed()){
                    it = this->erase(it);
                    invader = *it;
                    invader->Hide();
                }else{
                    invader->Animate();
                    switch(mCurrentDirection){
                        case Direction::Right:
                            if(invader->CanMoveRight(mRightBound)){
                                invader->MoveRight();
                            }else {
                                invader->MoveDown();
                                mCurrentDirection = Direction::Down;
                            }
                            break;
                        case Direction::Down:
                            invader->MoveDown();
                            break;
                        case Direction::Left:
                            if(invader->CanMoveLeft(mLeftBound)){
                                invader->MoveLeft();
                            }else{
                                invader->MoveDown();
                                mCurrentDirection = Direction::Down;
                            }
                            break;
                    }
                    ++it;
                }
            }

            // reset directional state after down movement
            if(mCurrentDirection == Direction::Down){
                mCurrentDirection = mNextDirectionAfterDown;
                if(mNextDirectionAfterDown == Direction::Left){
                    mNextDirectionAfterDown = Direction::Right;
                }else{
                    mNextDirectionAfterDown = Direction::Left;
                }
            }
        }
    }

private:
    Direction mCurrentDirection;
    Direction mNextDirectionAfterDown;
    int mLeftBound, mRightBound;
    int mAnimateSpeedMs;
    int mFrameStart;
};

#endif //SPACEINVADERS_INVADERLIST_H
