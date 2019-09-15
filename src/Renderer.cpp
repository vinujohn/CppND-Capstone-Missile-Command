//
// Created by Vinu on 9/13/19.
//

#include <iostream>
#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <cmath>

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
            "Space Invaders",
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

void Renderer::RenderBackground(const std::string &filePath) {
    SDL_Texture *texture = IMG_LoadTexture(mRenderer, filePath.c_str());
    ThrowIfError(
            texture == nullptr,
            "could not load texture for background");

    // Clear any other drawing
    SDL_RenderClear(mRenderer);

    // Draw the texture multiple times till it fills the whole window
    int textureWidth, textureHeight;
    SDL_QueryTexture(texture, nullptr, nullptr, &textureWidth, &textureHeight);
    for(int h = 0; h < std::ceil((float)mWindowHeight/textureHeight); h++){
        for(int w=0; w < std::ceil((float)mWindowWidth/textureWidth); w++){
            RenderTexture(texture, w * textureWidth, h * textureHeight, textureWidth, textureHeight);
        }
    }

    // Update the screen
    SDL_RenderPresent(mRenderer);
}

void Renderer::Cleanup() {
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
