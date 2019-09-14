//
// Created by Vinu on 9/13/19.
//

#ifndef SHOOTER_RENDERER_H
#define SHOOTER_RENDERER_H

#include "SDL.h";
#include <memory>;
#include <string>

class Renderer {
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    void ThrowIfError(bool isError, const std::string &errMsg);

    void Cleanup();

public:
    Renderer(int windowWidth, int windowHeight);

    ~Renderer();

    void RenderBackground(const std::string &path);
};

#endif //SHOOTER_RENDERER_H
