#include "SDL.h";
#include "Renderer.h";
#include <iostream>
#include <vector>

int main() {
    constexpr int windowWidth = 300;
    constexpr int windowHeight = 300;
    constexpr int windowOffset = 20;
    const std::string bgFile = "./assets/space.png";
    const std::string spriteFile = "./assets/sprites.png";
    const int FPS = 60;
    const int DELAY_TIME = 1000.0f / FPS;
    Uint32 frameStart, frameTime;


    Renderer r(windowWidth, windowHeight);

    r.LoadBackground(bgFile);

    // Load sprites
    std::vector<Renderer::SpriteAsset> enemies;
    enemies.push_back(Renderer::SpriteAsset{0, 0, 20, 14});
    enemies.push_back(Renderer::SpriteAsset{20, 0, 20, 14});
    enemies.push_back(Renderer::SpriteAsset{0, 14, 20, 14});
    enemies.push_back(Renderer::SpriteAsset{20, 14, 20, 14});
    enemies.push_back(Renderer::SpriteAsset{0, 28, 20, 14});
    enemies.push_back(Renderer::SpriteAsset{20, 28, 20, 14});
    auto ship = Renderer::SpriteAsset{20, 42, 20, 18};
    auto explosion = Renderer::SpriteAsset{0, 58, 20, 14};
    auto projectile = Renderer::SpriteAsset{20, 60, 20, 14};
    auto bomb = Renderer::SpriteAsset{0, 69, 20, 14};

    r.LoadSprites(spriteFile, enemies, ship, explosion, bomb, projectile);


    Game g(windowWidth, windowHeight, windowOffset);
    g.Start();

    bool isquit = false;
    SDL_Event event;
    while (!isquit) {
        if (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                isquit = true;
            }
        }

        const Uint8* currentKeyStates = SDL_GetKeyboardState( nullptr );

        frameStart = SDL_GetTicks();
        if(currentKeyStates[SDL_SCANCODE_RIGHT]){
            g.MoveRight();
        }
        if(currentKeyStates[SDL_SCANCODE_LEFT]){
            g.MoveLeft();
        }
        if(currentKeyStates[SDL_SCANCODE_SPACE]){
            g.Fire();
        }
        g.Update();
        r.Render(g);

        frameTime = SDL_GetTicks() - frameStart;
        if(frameTime < DELAY_TIME)
        {
            SDL_Delay((int)(DELAY_TIME - frameTime));
        }
    }

    std::cout << "Bye" << std::endl;
    return 0;
}