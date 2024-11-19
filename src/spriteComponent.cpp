#include "spriteComponent.h"
#include "actor.h"
#include "game.h"
#include <iostream>

spriteComponent::spriteComponent(actor* owner, int drawOrder)
: component(owner), mTexture(nullptr), mDrawOrder(drawOrder), mTextureHeight(0), mTextureWidth(0)
{
    mOwner -> getGame() -> addSprite(this);
    std::cout << "sprite added" << std::endl;
}

spriteComponent::~spriteComponent()
{
    mOwner -> getGame() -> removeSprite(this);
}

void spriteComponent::render(SDL_Renderer* renderer)
{
    if (mTexture)
    {
        SDL_Rect r;
        r.w = static_cast<int>(mTextureWidth * mOwner->getScale());
		r.h = static_cast<int>(mTextureHeight * mOwner->getScale());
		// Center the rectangle around the position of the owner
		r.x = static_cast<int>(mOwner->getPosition().x - r.w / 2);
		r.y = static_cast<int>(mOwner->getPosition().y - r.h / 2);

        SDL_RenderCopyEx(renderer, mTexture, nullptr, &r, 
        - math::ToDegrees(mOwner->getRotation()), nullptr, SDL_FLIP_NONE);
    }
}

void spriteComponent::setTexture(SDL_Texture* texture)
{
	mTexture = texture;
	SDL_QueryTexture(texture, nullptr, nullptr, &mTextureWidth, &mTextureHeight);
}