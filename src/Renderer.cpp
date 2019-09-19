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

void Renderer::RenderTexture(SDL_Texture *texture, int x, int y, int w, int h) {
    SDL_Rect dst;
    dst.x = x, dst.y = y, dst.w = w, dst.h = h;
    SDL_RenderCopy(mRenderer, texture, nullptr, &dst);
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

    mShipSprite = SDL_Rect{ship.x, ship.y, ship.w, ship.h};
    mProjectileSprite = SDL_Rect{projectile.x, projectile.y, projectile.w, projectile.h};
    mExplosionSprite = SDL_Rect{explosion.x, explosion.y, explosion.w, explosion.h};

    for(int i = 0; i < enemies.size(); i++){
        mEnemySprites.push_back(SDL_Rect{enemies[i].x, enemies[i].y, enemies[i].w, enemies[i].h});
    }


/*
    auto r = SDL_Rect{ship.x, ship.y, ship.w, ship.h};
    auto d = SDL_Rect{30, 0, ship.w, ship.h};
    SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &r, &d);

    auto r2 = SDL_Rect{explosion.x, explosion.y, explosion.w, explosion.h};
    auto d2 = SDL_Rect{60, 0, explosion.w, explosion.h};
    SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &r2, &d2);

    auto r3 = SDL_Rect{projectile.x, projectile.y, projectile.w, projectile.h};
    auto d3 = SDL_Rect{90, 0, projectile.w, projectile.h};
    SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &r3, &d3);

    auto r4 = SDL_Rect{bomb.x, bomb.y, bomb.w, bomb.h};
    auto d4 = SDL_Rect{120, 0, bomb.w, bomb.h};
    SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &r4, &d4);

    SDL_RenderPresent(mRenderer);
    */
}

void Renderer::Render(Game g) {
    SDL_RenderClear(mRenderer);

    SDL_RenderCopy(mRenderer, mBackground, nullptr, nullptr);

    auto d = SDL_Rect{g.Ship.x, g.Ship.y, mShipSprite.w, mShipSprite.h};
    //std::cout << "Ship x: " << g.Ship.x << " y: " << g.Ship.y << std::endl;
    SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &mShipSprite, &d);

    if(g.IsFiring()){
        auto p = SDL_Rect{g.Projectile.x, g.Projectile.y, mProjectileSprite.w, mProjectileSprite.h};
        SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &mProjectileSprite, &p);
    }

    if(!g.Enemy.destroyed){
        auto e = SDL_Rect{g.Enemy.x, g.Enemy.y, mEnemySprites[g.Enemy.currentFrame].w, mEnemySprites[g.Enemy.currentFrame].h};
        auto temp = mEnemySprites[g.Enemy.currentFrame];
        SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &temp, &e);
    }else{
        auto e = SDL_Rect{g.Enemy.x, g.Enemy.y, mExplosionSprite.w, mExplosionSprite.h};
        auto temp = mEnemySprites[g.Enemy.currentFrame];
        SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &mExplosionSprite, &e);
    }

    SDL_RenderPresent(mRenderer);

    std::string score = "Space Invaders - Score: " + std::to_string(g.Score());

    SDL_SetWindowTitle(mWindow, score.c_str());
}
