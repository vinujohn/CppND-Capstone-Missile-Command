//
// Created by Vinu on 9/28/19.
//

#ifndef SPACEINVADERS_INVADER_H
#define SPACEINVADERS_INVADER_H

#include "Sprite.h"
#include <iostream>
#include <memory>

class Invader : public Sprite {
public:
    Invader(std::vector<Rect> animations, int startAnimationIndex);

    void Animate();

    void Destroy();

    bool Destroyed();

    bool CanMoveRight(int bound);

    void MoveRight();;

    bool CanMoveLeft(int bound);

    void MoveLeft();

    void MoveDown();

    bool CanMoveDown(int bound);

    void Reset() override;

private:
    bool mDestroyed = false;
    int mStartAnimationIndex;
};

#endif //SPACEINVADERS_INVADER_H
