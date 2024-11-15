#pragma once

#include "component.h"
#include <SDL2/SDL.h>

class spriteComponent : public component
{
public:
    spriteComponent(class actor* owner, int drawOrder = 100);
    ~spriteComponent();

    virtual void render(SDL_Renderer* renderer);
    virtual void setTexture(SDL_Texture* texture);

    int getDrawOrder() const { return mDrawOrder; }
    int getTextureHeight() const { return mTextureHeight; }
    int getTextureWidth() const { return mTextureWidth; }

protected:
    SDL_Texture* mTexture;
    int mDrawOrder;
    int mTextureHeight;
    int mTextureWidth;
};