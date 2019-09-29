//
// Created by Vinu on 9/29/19.
//

#ifndef SPACEINVADERS_INVADERLIST_H
#define SPACEINVADERS_INVADERLIST_H
#include <vector>
#include "Invader.h"

class InvaderList : public std::vector<Invader> {
public:
    InvaderList(int animationSpeedMs):mMovingLeft(false), mAnimateSpeedMs(animationSpeedMs){}

private:
    bool mMovingLeft;
    int mAnimateSpeedMs;
};

#endif //SPACEINVADERS_INVADERLIST_H
