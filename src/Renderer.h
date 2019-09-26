//
// Created by Vinu on 9/13/19.
//

#ifndef SPACE_INVADERS_RENDERER_H
#define SPACE_INVADERS_RENDERER_H

#include "SDL.h"
#include <memory>
#include <string>
#include <vector>
#include "Game.h"

//TODO remove this
class Game;

class Renderer {
private:
    SDL_Window *mWindow;
    SDL_Renderer *mRenderer;
    SDL_Texture *mBackground;
    SDL_Texture *mSpriteSheetTexture;
    std::vector<SDL_Rect> mEnemySprites;
    SDL_Rect mShipSprite;
    SDL_Rect mExplosionSprite;
    SDL_Rect *mBombSprite;
    SDL_Rect mProjectileSprite;

    int mWindowWidth, mWindowHeight;

    void ThrowIfError(bool isError, const std::string &errMsg);

    void RenderTexture(SDL_Texture *texture, int x, int y, int w, int h);

    void Cleanup();

public:
    struct SpriteAsset{
        int x,y,w,h;
    };

    Renderer(int windowWidth, int windowHeight);

    ~Renderer();

    void LoadBackground(const std::string &filePath);
    void LoadSprites(const std::string &filePath,
                     const std::vector<SpriteAsset>& enemies,
                     SpriteAsset ship,
                     SpriteAsset explosion,
                     SpriteAsset bomb,
                     SpriteAsset projectile);
    void Render(Game &g);
};

#endif //SPACE_INVADERS_RENDERER_H
