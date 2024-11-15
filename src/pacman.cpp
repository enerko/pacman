#include "pacman.h"
#include "game.h"
#include "spriteComponent.h"
#include <SDL2/SDL.h>
#include <iostream>

pacman::pacman(game* gameInstance): actor(gameInstance)
{
    spriteComponent* sprite = new spriteComponent(this);
    SDL_Texture* tex = (gameInstance -> getTexture("Assets/pacman.png"));
    sprite -> setTexture(tex);
}

pacman::~pacman()
{

}