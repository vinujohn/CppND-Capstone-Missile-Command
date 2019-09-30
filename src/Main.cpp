#include "SDL.h"
#include "Renderer.h"
#include "KeyboardController.h"
#include <iostream>
#include <vector>
#include "Game.h"

int main() {
    constexpr int windowWidth = 300;
    constexpr int windowHeight = 300;
    constexpr int windowOffset = 20;
    const std::string bgFile = "./assets/space.png";
    const std::string spriteFile = "./assets/sprites.png";
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;

    Renderer r(windowWidth, windowHeight, bgFile, spriteFile);

    //auto bomb = Renderer::SpriteAsset{0, 69, 20, 14};

    Game g(windowWidth, windowHeight, windowOffset);
    auto kc = KeyboardController();

    g.Run(DELAY_TIME, kc, r);

    std::cout << "Bye" << std::endl;
    return 0;
}

