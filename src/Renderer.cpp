//
// Created by Vinu on 9/13/19.
//

#include <iostream>
#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <cmath>
#include <vector>

void Renderer::ThrowIfError(bool isError, const std::string &errMsg) {
    if (isError) {
        std::cerr << "Renderer: " << errMsg << ". SDL_Error: " << SDL_GetError() << std::endl;
        Cleanup();
        throw std::runtime_error(errMsg);
    }
}

Renderer::Renderer(int windowWidth, int windowHeight)
    : mWindowWidth(windowWidth), mWindowHeight(windowHeight) {
    // initialize SDL
    ThrowIfError(
            SDL_Init(SDL_INIT_VIDEO) != 0,
            "could not initialize SDL");

    // initialize the image subsystem
    ThrowIfError(
            (IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG,
            "could not initialize SDL image subsystem");

    // create a window
    mWindow = SDL_CreateWindow(
            "Space Invaders - Score: 0",
            SDL_WINDOWPOS_CENTERED,
            SDL_WINDOWPOS_CENTERED,
            windowWidth,
            windowHeight,
            SDL_WINDOW_SHOWN);
    ThrowIfError(
            mWindow == nullptr,
            "could not initialize window");

    // create a renderer
    mRenderer = SDL_CreateRenderer(
            mWindow,
            -1,
            SDL_RENDERER_ACCELERATED);
    ThrowIfError(
            mRenderer == nullptr,
            "could not create renderer");



    std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Destructor for renderer called ..." << std::endl;
    Cleanup();
}

void Renderer::LoadBackground(const std::string &filePath) {
    mBackground = IMG_LoadTexture(mRenderer, filePath.c_str());
    ThrowIfError(
            mBackground == nullptr,
            "could not load texture for background");
}

void Renderer::Cleanup() {
    if(mBackground != nullptr){
        SDL_DestroyTexture(mBackground);
    }
    if(mSpriteSheetTexture != nullptr){
        SDL_DestroyTexture(mSpriteSheetTexture);
    }
    if (mRenderer != nullptr) {
        SDL_DestroyRenderer(mRenderer);
    }
    if (mWindow != nullptr) {
        SDL_DestroyWindow(mWindow);
    }
    IMG_Quit();
    SDL_Quit();
}

void Renderer::LoadSprites(
        const std::string &filePath,
        const std::vector<SpriteAsset>& enemies,
        SpriteAsset ship,
        SpriteAsset explosion,
        SpriteAsset bomb,
        SpriteAsset projectile) {

    mSpriteSheetTexture = IMG_LoadTexture(mRenderer, filePath.c_str());
    ThrowIfError(
            mSpriteSheetTexture == nullptr,
            "could not load texture for sprites");

    mExplosionSprite = SDL_Rect{explosion.x, explosion.y, explosion.w, explosion.h};

    for(int i = 0; i < enemies.size(); i++){
        mEnemySprites.push_back(SDL_Rect{enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h});
    }
}

void Renderer::Render(Game &g) {
    SDL_RenderClear(mRenderer);

    SDL_RenderCopy(mRenderer, mBackground, nullptr, nullptr);

    for(auto s : g.Sprites()){
        if(s->Displayed()) {
            auto a = s->GetCurrentAnimation();
            auto src = SDL_Rect{a.x, a.y, a.w, a.h};
            auto dst = SDL_Rect{s->X(), s->Y(), s->W(), s->H()};
            SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &src, &dst);
        }
    }

    SDL_RenderPresent(mRenderer);

    std::string score = "Space Invaders - Score: " + std::to_string(g.Score());

    SDL_SetWindowTitle(mWindow, score.c_str());
}
