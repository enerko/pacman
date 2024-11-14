#include "game.h"
#include "constants.h"

game::game():mWindow(nullptr)
,mRenderer(nullptr) ,mIsRunning(true)
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
		generateOutput();
		updateGame();
	}
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
	
}

void game::generateOutput()
{
	SDL_SetRenderDrawColor(mRenderer, 0, 0, 0, 255);
	SDL_RenderClear(mRenderer);

    // Render game objects here

    SDL_RenderPresent(mRenderer);
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
}

void game::shutdown()
{
    unloadData();
    SDL_DestroyRenderer(mRenderer);
	SDL_DestroyWindow(mWindow);
	SDL_Quit();
}
