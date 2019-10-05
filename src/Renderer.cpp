//
// Created by Vinu on 9/13/19.
//

#include <iostream>
#include "Renderer.h"
#include "SDL.h"
#include "SDL_image.h"
#include <vector>

void Renderer::ThrowIfError(bool isError, const std::string &errMsg) {
    if (isError) {
        std::cerr << "Renderer: " << errMsg << ". SDL_Error: " << SDL_GetError() << std::endl;
        Cleanup();
        throw std::runtime_error(errMsg);
    }
}

Renderer::Renderer(int windowWidth, int windowHeight, const std::string &backgroundFilePath,
                   const std::string &spriteFilePath)
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

    mBackgroundTexture = IMG_LoadTexture(mRenderer, backgroundFilePath.c_str());
    ThrowIfError(
            mBackgroundTexture == nullptr,
            "could not load texture for background");

    mSpriteSheetTexture = IMG_LoadTexture(mRenderer, spriteFilePath.c_str());
    ThrowIfError(
            mSpriteSheetTexture == nullptr,
            "could not load texture for sprites");

    std::cout << "Renderer initialized" << std::endl;
}

Renderer::~Renderer() {
    std::cout << "Destructor for renderer called ..." << std::endl;
    Cleanup();
}

void Renderer::Cleanup() {
    if (mBackgroundTexture != nullptr) {
        SDL_DestroyTexture(mBackgroundTexture);
    }
    if (mSpriteSheetTexture != nullptr) {
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

void Renderer::Render(const std::vector<std::shared_ptr<Sprite>> &sprites) const {
    SDL_RenderClear(mRenderer);

    SDL_RenderCopy(mRenderer, mBackgroundTexture, nullptr, nullptr);

    for (auto s : sprites) {
        if (s->Displayed()) {
            auto a = s->GetCurrentAnimation();
            auto src = SDL_Rect{a.x, a.y, a.w, a.h};
            auto dst = SDL_Rect{s->X(), s->Y(), s->W(), s->H()};
            SDL_RenderCopy(mRenderer, mSpriteSheetTexture, &src, &dst);
        }
    }

    SDL_RenderPresent(mRenderer);
}

void Renderer::UpdateScore(int score) const {
    std::string scoreStr = "Space Invaders - Score: " + std::to_string(score);

    SDL_SetWindowTitle(mWindow, scoreStr.c_str());
}

MessageBoxOutput Renderer::DisplayEndGameMessage(std::string message, int score) const {
    const SDL_MessageBoxButtonData buttons[] = {
            {SDL_MESSAGEBOX_BUTTON_RETURNKEY_DEFAULT, 1, "YES"},
            {SDL_MESSAGEBOX_BUTTON_ESCAPEKEY_DEFAULT, 2, "EXIT"},
    };

    message = message + " Final Score - " + std::to_string(score);

    const SDL_MessageBoxData messageboxdata = {
            SDL_MESSAGEBOX_INFORMATION,
            mWindow,
            "Game Over.  Do you want to play again?",
            message.c_str(),
            SDL_arraysize(buttons),
            buttons,
            nullptr
    };

    int buttonId;
    SDL_ShowMessageBox(&messageboxdata, &buttonId);

    return buttonId == (int) MessageBoxOutput::Yes ? MessageBoxOutput::Yes : MessageBoxOutput::Exit;
}
