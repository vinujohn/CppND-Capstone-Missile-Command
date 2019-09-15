#include "SDL.h";
#include "Renderer.h";
#include <iostream>

int main() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 800;
    const std::string bgFile = "./assets/space.png";
    const std::string spriteFile = "./assets/sprites.png";

    Renderer r(windowWidth, windowHeight);

    r.RenderBackground(bgFile);

    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}