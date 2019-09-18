#include "SDL.h";
#include "Renderer.h";
#include <iostream>
#include <vector>

int main() {
    constexpr int windowWidth = 800;
    constexpr int windowHeight = 800;
    const std::string bgFile = "./assets/space.png";
    const std::string spriteFile = "./assets/sprites.png";

    Renderer r(windowWidth, windowHeight);

    //r.RenderBackground(bgFile);

    // Load sprites
    std::vector<Renderer::Rectangle> enemies;
    enemies.push_back(Renderer::Rectangle{50,1850,50,50});
    auto ship = Renderer::Rectangle{420, 1920, 50, 50};
    auto explosion = Renderer::Rectangle{430, 270, 30, 30};
    auto bullet = Renderer::Rectangle{430, 1870, 30, 30};
    r.LoadSprites(spriteFile, enemies, 2, ship, explosion, bullet);

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