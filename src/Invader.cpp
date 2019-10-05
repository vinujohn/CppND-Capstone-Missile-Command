//
// Created by Vinu on 10/5/19.
//

#include "Invader.h"

Invader::Invader(std::vector<Rect> animations, int startAnimationIndex)
        : mStartAnimationIndex(startAnimationIndex)
        , mDestroyed(false), Sprite(animations) {
    SetAnimationIndex(startAnimationIndex);
}

void Invader::Animate() {
    SetAnimationIndex((GetAnimationIndex() + 1) % 2);
}

void Invader::Destroy() {
    SetAnimationIndex(2);
    mDestroyed = true;
}

bool Invader::Destroyed() {
    return mDestroyed;
}

bool Invader::CanMoveRight(int bound) {
    return X() + W() < bound;
}

void Invader::MoveRight() {
    Move(X() + W(), Y());
}

bool Invader::CanMoveLeft(int bound) {
    return X() - W() >= bound;
}

void Invader::MoveLeft() {
    Move(X() - W(), Y());
}

void Invader::MoveDown() {
    Move(X(), Y() + H());
}

bool Invader::CanMoveDown(int bound) {
    return Y() + H() < bound;
}

void Invader::Reset() {
    SetAnimationIndex(mStartAnimationIndex);
    mDestroyed = false;
}
