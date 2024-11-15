#include <SDL2/SDL.h>
#include <iostream>
#include <vector>
#include <unordered_map>

class game
{
public:
    game();
    bool initialize();
    void runLoop();
    void shutdown();

    void addActor(class actor* actorToAdd);
    void removeActor(class actor* actorToRemove);

    void addSprite(class spriteComponent* sprite);
    void removeSprite(class spriteComponent* sprite);

    SDL_Texture* getTexture(const std::string& fileName);

private:
    void processInput();
    void updateGame();
    void generateOutput();

    void loadData();
    void unloadData();

    void render();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    bool mIsRunning;

    Uint32 mTicksCount;

	std::vector<class actor*> mActors; // All the actors in the game
    std::vector<class actor*> mPendingActors;

    std::vector<class spriteComponent*> mSprites;

    bool mAreActorsUpdating;

	std::unordered_map<std::string, SDL_Texture*> mTextures; // Map of textures loaded
};