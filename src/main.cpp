#include "SDL.h";
#include "renderer.h";
#include <iostream>

int main() {
    constexpr int windowWidth = 640;
    constexpr int windowHeight = 640;
    const std::string bgFile = "./assets/background/space.png";

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