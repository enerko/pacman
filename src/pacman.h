#pragma once
#include "actor.h"
#include "SDL2/SDL_stdinc.h"

class pacman : public actor
{
public:
    enum class direction
    {
        NONE = 0, UP, DOWN, LEFT, RIGHT
    };

    pacman(class game* gameInstance);
    ~pacman();

    void updateActor(float deltaTime) override;

    void processKeyboard(const uint8_t* state);

private:
    direction mCurrentDirection;
    float mSpeed = 200.0f; // Pixels per second

	float mRightSpeed;
	float mDownSpeed;
};