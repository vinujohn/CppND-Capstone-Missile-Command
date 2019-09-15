//
// Created by Vinu on 9/13/19.
//

#ifndef SPACE_INVADERS_RENDERER_H
#define SPACE_INVADERS_RENDERER_H

#include "SDL.h";
#include <memory>;
#include <string>

class Renderer {
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;

    int mWindowWidth, mWindowHeight;

    void ThrowIfError(bool isError, const std::string &errMsg);

    void RenderTexture(SDL_Texture *texture, int x, int y, int w, int h);

    void Cleanup();

public:
    Renderer(int windowWidth, int windowHeight);

    ~Renderer();

    void RenderBackground(const std::string &path);
};

#endif //SPACE_INVADERS_RENDERER_H
