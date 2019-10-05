#include "Renderer.h"
#include "KeyboardController.h"
#include <iostream>
#include <vector>
#include "Game.h"

int main() {
    constexpr int windowWidth = 300;
    constexpr int windowHeight = 350;
    constexpr int windowOffset = 20;

    const std::string bgFile = "./assets/space.png";
    const std::string spriteFile = "./assets/sprites.png";

    constexpr int FPS = 60;
    constexpr int DELAY_TIME = static_cast<const int>(1000.0f / FPS);

    const std::vector<Rect> projectileAnimations {
        {20, 60, 20, 14}
    };
    const std::vector<Rect> cannonAnimations {
        {20, 42, 20, 18},
        {0,  42, 20, 18}
    };
    const std::vector<Rect> bombAnimations {
        {0, 69, 20, 14}
    };
    const std::vector<std::vector<Rect>> invaderAnimations {
        {
                {0, 0,  20, 14},
                {20, 0,  20, 14},
                {0, 58, 20, 14}
        },
        {
                {0, 14, 20, 14},
                {20, 14, 20, 14},
                {0, 58, 20, 14}
        },
        {
                {0, 28, 20, 14},
                {20, 28, 20, 14},
                {0, 58, 20, 14}
        }
    };

    constexpr int moveCannonByPx = 2;
    constexpr int enemyAnimationSpeedMs = 500;
    constexpr int increaseAnimationSpeedByMs = 20;
    constexpr int numInvadersPerRow = 5;
    const int numInvaderRows = invaderAnimations.size();

    /* Build game assets */
    auto projectile = std::shared_ptr<Sprite>(new Sprite(projectileAnimations));
    auto cannon = std::shared_ptr<Cannon>(new Cannon(cannonAnimations, windowWidth, windowHeight, projectile, moveCannonByPx));
    auto bomb = std::shared_ptr<Sprite>(new Sprite(bombAnimations));
    auto invaderList = std::shared_ptr<InvaderList>(
            new InvaderList(enemyAnimationSpeedMs, increaseAnimationSpeedByMs, numInvaderRows, numInvadersPerRow,
                            windowOffset, windowWidth - windowOffset, windowHeight - windowOffset, bomb));

    // create and add invaders to list
    for (int row = 0; row < numInvaderRows; row++) {
        for (int col = 0; col < numInvadersPerRow; col++) {
            auto invader = std::shared_ptr<Invader>(new Invader(invaderAnimations[row], col % 2));
            invaderList->push_back(invader);
        }
    }

    Game g(windowWidth, windowHeight, windowOffset, projectile, cannon, bomb, invaderList);

    KeyboardController controller;
    Renderer renderer(windowWidth, windowHeight, bgFile, spriteFile);

    g.Run(DELAY_TIME, controller, renderer);

    std::cout << "Main ended" << std::endl;
    return 0;
}

