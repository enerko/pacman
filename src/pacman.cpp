#include "pacman.h"
#include "game.h"
#include "spriteComponent.h"
#include <SDL2/SDL.h>
#include <iostream>

pacman::pacman(game* gameInstance): actor(gameInstance), mSpeed(0)
, mCurrentDirection(direction::NONE)
{
    spriteComponent* sprite = new spriteComponent(this);
    SDL_Texture* tex = (gameInstance -> getTexture("Assets/pacman.png"));
    sprite -> setTexture(tex);
}

pacman::~pacman()
{

}

void pacman::updateActor(float deltaTime)
{
    // Update position based on current direction
    Vector2 pos = getPosition(); // Assume `getPosition` returns Pac-Man's position

	pos.x += mRightSpeed * deltaTime;
	pos.y += mDownSpeed * deltaTime;
	// Restrict position to left half of screen
	if (pos.x < 25.0f)
	{
		pos.x = 25.0f;
	}
	else if (pos.x > 500.0f)
	{
		pos.x = 500.0f;
	}
	if (pos.y < 25.0f)
	{
		pos.y = 25.0f;
	}
	else if (pos.y > 743.0f)
	{
		pos.y = 743.0f;
	}

    // TODO: Add collision detection with walls
    setPosition(pos); // Assume `setPosition` sets Pac-Man's position
}

void pacman::processKeyboard(const uint8_t* state)
{
    mRightSpeed = 0.0f;
	mDownSpeed = 0.0f;
	// right/left
	if (state[SDL_SCANCODE_D])
	{
		mRightSpeed += 250.0f;
	}
	if (state[SDL_SCANCODE_A])
	{
		mRightSpeed -= 250.0f;
	}
	// up/down
	if (state[SDL_SCANCODE_S])
	{
		mDownSpeed += 300.0f;
	}
	if (state[SDL_SCANCODE_W])
	{
		mDownSpeed -= 300.0f;
	}
}