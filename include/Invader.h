//
// Created by Vinu on 9/28/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

#include "Sprite.h"
#include <iostream>

class Invader : public Sprite {
public:
    Invader(std::vector<Rect> animations, int startAnimationIndex)
            : mStartAnimationIndex(startAnimationIndex), mDestroyed(false), Sprite(animations) {
        SetAnimationIndex(startAnimationIndex);
    }

    void Animate() {
        SetAnimationIndex((GetAnimationIndex() + 1) % 2);
    }

    void Destroy() {
        SetAnimationIndex(2);
        mDestroyed = true;
    }

    bool Destroyed() {
        return mDestroyed;
    }

    bool CanMoveRight(int bound) {
        return X() + W() < bound;
    }

    void MoveRight() {
        Move(X() + W(), Y());
    };

    bool CanMoveLeft(int bound) {
        return X() - W() >= bound;
    }

    void MoveLeft() {
        Move(X() - W(), Y());
    }

    void MoveDown() {
        Move(X(), Y() + H());
    }

    bool CanMoveDown(int bound) {
        return Y() + H() < bound;
    }

    void Reset() {
        SetAnimationIndex(mStartAnimationIndex);
        mDestroyed = false;
    }

private:
    bool mDestroyed = false;
    int mStartAnimationIndex;
};

#endif //SPACEINVADERS_INVADER_H
