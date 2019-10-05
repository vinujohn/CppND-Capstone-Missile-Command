//
// Created by Vinu on 10/5/19.
//

#include "Sprite.h"

Sprite::Sprite(const std::vector<Rect>& animations)
        : mAnimations(animations), mDisplayed(false), mCurrentAnimationIndex(0) {

    //Take height and width from first animation.
    mPosition = Rect{0, 0, animations[0].w, animations[0].h};
}

void Sprite::Hide() { mDisplayed = false; }

void Sprite::Display() { mDisplayed = true; }

bool Sprite::Displayed() { return mDisplayed; }

int Sprite::X() { return mPosition.x; }

int Sprite::Y() { return mPosition.y; }

int Sprite::W() { return mPosition.w; }

int Sprite::H() { return mPosition.h; }

void Sprite::SetAnimationIndex(int index) { mCurrentAnimationIndex = index; }

int Sprite::GetAnimationIndex() { return mCurrentAnimationIndex; }

Rect Sprite::GetCurrentAnimation() { return mAnimations[mCurrentAnimationIndex]; }

void Sprite::Move(int x, int y) {
    mPosition.x = x;
    mPosition.y = y;
}

bool Sprite::Collided(Sprite &sprite) {
    if (this->X() >= sprite.X() && this->X() <= sprite.X() + sprite.W()) {
        if (this->Y() <= sprite.Y() && (this->Y() + this->H()) >= sprite.Y()) {
            return true;
        }
    }
    return false;
}

void Sprite::Reset() {
    this->Hide();
}
