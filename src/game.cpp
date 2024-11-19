#include "game.h"
#include "actor.h"
#include "constants.h"
#include "spriteComponent.h"
#include "pacman.h"
#include <SDL2/SDL_image.h>
#include <iostream>
#include <algorithm>

game::game():mWindow(nullptr)
,mRenderer(nullptr) ,mIsRunning(true), mAreActorsUpdating(false)
{

}

bool game::initialize()
{
    if (SDL_Init(SDL_INIT_VIDEO|SDL_INIT_AUDIO) != 0)
	{
		SDL_Log("Unable to initialize SDL: %s", SDL_GetError());
		return false;
	}
	
	mWindow = SDL_CreateWindow("Pacman", 100, 100, screenWidth, screenHeight, 0);
	if (!mWindow)
	{
		SDL_Log("Failed to create window: %s", SDL_GetError());
		return false;
	}
	
	mRenderer = SDL_CreateRenderer(mWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!mRenderer)
	{
		SDL_Log("Failed to create renderer: %s", SDL_GetError());
		return false;
	}
	
	loadData();

	mTicksCount = SDL_GetTicks();
	
	return true;

}

void game::loadData()
{
    // load data here
	mPlayer = new pacman(this);
	mPlayer -> setPosition(Vector2(100.0f, 384.0f));
}

void game::unloadData()
{
    // unload data here
}

void game::runLoop()
{	
	while (mIsRunning)
	{
		processInput();
		updateGame();
		render();
	}
}

void game::render()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);
	
	// Draw all sprite components
	for (auto sprite : mSprites)
	{
		sprite->render(mRenderer);
	}

	SDL_RenderPresent(mRenderer);
}

void game::processInput()
{
    SDL_Event event;
	while (SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			// If we get an SDL_QUIT event, end loop
			case SDL_QUIT:
				mIsRunning = false;
				break;
		}
	}

    // Process player input here
	const uint8_t* state = SDL_GetKeyboardState(nullptr);

    mPlayer->processKeyboard(state);
}

void game::updateGame()
{
	// limit frames to 60 FPS
	while (!SDL_TICKS_PASSED(SDL_GetTicks(), mTicksCount + 16));

	float deltaTime = (SDL_GetTicks() - mTicksCount) / 1000.0f;

    // limit deltaTime to a max of 0.05 seconds to handle situations where the frame rate drops significantly
	if (deltaTime > 0.05f)
	{
		deltaTime = 0.05f;
	}
	mTicksCount = SDL_GetTicks();

    // Update game objects here
	updateActors(deltaTime);
}

void game::updateActors(float deltaTime)
{
	// Update all actors
	mAreActorsUpdating = true;
	for (auto actor : mActors)
	{
		actor->update(deltaTime);
	}
	mAreActorsUpdating = false;

	// Move any pending actors to mActors
	for (auto pending : mPendingActors)
	{
		mActors.emplace_back(pending);
	}
	mPendingActors.clear();

	// Add any dead actors to a temp vector
	std::vector<actor*> deadActors;
	for (auto actor : mActors)
	{
		if (actor->getState() == actor::state::EDead)
		{
			deadActors.emplace_back(actor);
		}
	}

	// Delete dead actors (which removes them from mActors)
	for (auto actor : deadActors)
	{
		delete actor;
	}
}

void game::shutdown()
{
    unloadData();
    SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}

void game::addActor(actor* actorToAdd)
{
	if (mAreActorsUpdating)
		mPendingActors.emplace_back(actorToAdd);
	else
		mActors.emplace_back(actorToAdd);
}

void game::removeActor(actor* actorToRemove)
{
	// If it is in pending actors
	auto iter = std::find(mPendingActors.begin(), mPendingActors.end(), actorToRemove);
	if (iter != mPendingActors.end())
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mPendingActors.end() - 1);
		mPendingActors.pop_back();
	}

	// If it is in actors
	iter = std::find(mActors.begin(), mActors.end(), actorToRemove);
	if (iter != mActors.end() && actorToRemove->getState() == actor::state::EDead)
	{
		// Swap to end of vector and pop off (avoid erase copies)
		std::iter_swap(iter, mActors.end() - 1);
		mActors.pop_back();
	}
}

void game::addSprite(spriteComponent* sprite)
{
	// Find the insertion point in the sorted vector
	// (The first element with a higher draw order than me)
	int myDrawOrder = sprite->getDrawOrder();
	auto iter = mSprites.begin();
	for ( ; iter != mSprites.end(); ++iter)
	{
		if (myDrawOrder < (*iter)->getDrawOrder())
		{
			break;
		}
	}

	// Inserts element before position of iterator
	mSprites.insert(iter, sprite);
}

void game::removeSprite(spriteComponent* sprite)
{
	// (We can't swap because it ruins ordering)
	auto iter = std::find(mSprites.begin(), mSprites.end(), sprite);
	mSprites.erase(iter);
}

SDL_Texture* game::getTexture(const std::string& fileName)
{
	SDL_Texture* tex = nullptr;
	// Is the texture already in the map?
	auto iter = mTextures.find(fileName);
	if (iter != mTextures.end())
	{
		tex = iter->second;
	}
	else
	{
		// Load from file
		SDL_Surface* surf = IMG_Load(fileName.c_str());
		if (!surf)
		{
			SDL_Log("Failed to load texture file %s", fileName.c_str());
			return nullptr;
		}

		// Create texture from surface
		tex = SDL_CreateTextureFromSurface(mRenderer, surf);
		SDL_FreeSurface(surf);
		if (!tex)
		{
			SDL_Log("Failed to convert surface to texture for %s", fileName.c_str());
			return nullptr;
		}

		mTextures.emplace(fileName.c_str(), tex);
	}
	return tex;
}
