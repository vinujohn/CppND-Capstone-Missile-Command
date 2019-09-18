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
    SDL_Texture *mSpriteSheetTexture;
    SDL_Rect *mEnemySprites;

    int mWindowWidth, mWindowHeight;

    void ThrowIfError(bool isError, const std::string &errMsg);

    void RenderTexture(SDL_Texture *texture, int x, int y, int w, int h);

    void Cleanup();

public:
    struct Rectangle{
        int x,y,w,h;
    };

    Renderer(int windowWidth, int windowHeight);

    ~Renderer();

    void RenderBackground(const std::string &path);
    void LoadSprites(const std::string &filePath,
            std::vector<Rectangle> enemies,
            int numEnemyFrames,
            Rectangle ship,
            Rectangle explosion,
            Rectangle bullet);
};

#endif //SPACE_INVADERS_RENDERER_H
