//
// Created by Vinu on 9/28/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

#include "Sprite.h"

class Invader : public Sprite{
public:
    Invader(std::vector<Rect> animations, int startAnimationIndex) : Sprite(animations){
        SetAnimationIndex(startAnimationIndex);
    }

    void Animate(){
        SetAnimationIndex((GetAnimationIndex() + 1) % 2);
    }

    void Destroy(){
        SetAnimationIndex(2);
        mDestroyed = true;
    }

    // TODO remove this later
    bool mMovingLeft = false;
    bool mDestroyed = false;
};

#endif //SPACEINVADERS_INVADER_H
