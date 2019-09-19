//
// Created by Vinu on 9/19/19.
//

#ifndef SPACEINVADERS_SPRITE_H
#define SPACEINVADERS_SPRITE_H


#include <string>

struct Coord2D{
    int x, y, w, h;
};

struct Sprite {
    Coord2D Source;
    std::string Name;
};

struct AnimatableSprite : public Sprite {

};


#endif //SPACEINVADERS_SPRITE_H
