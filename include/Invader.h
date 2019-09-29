//
// Created by Vinu on 9/28/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

#include "Sprite.h"

class Invader : public Sprite{
public:
    Invader(std::vector<Rect> animations, int startAnimationIndex) : mDestroyed(false), Sprite(animations){
        SetAnimationIndex(startAnimationIndex);
    }

    void Animate(){
        SetAnimationIndex((GetAnimationIndex() + 1) % 2);
    }

    void Destroy(){
        SetAnimationIndex(2);
        mDestroyed = true;
    }

    bool Destroyed(){
        return mDestroyed;
    }

    bool CanMoveRight(int bound){
        if(X() + W() <= bound){
            return true;
        }
        return false;
    }

    void MoveRight(){
        Move(X() + W(),Y());
    };

    bool CanMoveLeft(int bound){
        if(X() - W() >= bound){
            return true;
        }
        return false;
    }

    void MoveLeft(){
        Move(X() - W(), Y());
    }

    void MoveDown(){
        Move(X(), Y() + H());
    }

private:
    bool mDestroyed = false;
};

#endif //SPACEINVADERS_INVADER_H
