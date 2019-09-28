//
// Created by Vinu on 9/21/19.
//

#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H

#include <vector>

struct Rect{
    int x, y, w, h;
};

class Sprite {
public:
    Sprite(std::vector<Rect> animations)
        : mAnimations(animations), mDisplayed(false), mCurrentAnimationIndex(0){
        //Take height and width from first animation for now.
        mScreen = Rect{0,0, animations[0].w, animations[0].h};
    }

    void Hide(){mDisplayed = false;}
    void Display(){mDisplayed = true;}
    bool Displayed(){return mDisplayed;}

    const int X(){return mScreen.x;}
    const int Y(){return mScreen.y;}
    const int W(){return mScreen.w;}
    const int H(){return mScreen.h;}

    void SetAnimationIndex(int index){ mCurrentAnimationIndex = index;}
    int GetAnimationIndex(){return mCurrentAnimationIndex;}
    const Rect GetCurrentAnimation(){return mAnimations[mCurrentAnimationIndex];}

    void Move(int x, int y){
        mScreen.x = x;
        mScreen.y = y;
    }

    bool Collided(Sprite &sprite){
        if(this->X() >= sprite.X() && this->X() <= sprite.X() + sprite.W()){
            if((this->Y() + this->H()) >= sprite.Y()){
                return true;
            }
        }
        return false;
    }

private:
    std::vector<Rect> mAnimations;
    Rect mScreen;
    bool mDisplayed;
    int mCurrentAnimationIndex;
};


#endif //SPACEINVADERS_SPRITE_H
