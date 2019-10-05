//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H

#include <vector>

struct Rect {
    int x, y, w, h;
};

class Sprite {
public:
    Sprite(const std::vector<Rect>& animations);

    void Hide();

    void Display();

    bool Displayed();

    int X();

    int Y();

    int W();

    int H();

    void SetAnimationIndex(int index);

    int GetAnimationIndex();

    Rect GetCurrentAnimation();

    void Move(int x, int y);

    bool Collided(Sprite &sprite);

    virtual void Reset();

private:
    std::vector<Rect> mAnimations;
    Rect mPosition;
    bool mDisplayed;
    int mCurrentAnimationIndex;
};


#endif //SPACEINVADERS_SPRITE_H
