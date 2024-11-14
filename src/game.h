#include <SDL2/SDL.h>

class game
{
public:
    game();
    bool initialize();
    void runLoop();
    void shutdown();

private:
    void processInput();
    void updateGame();
    void generateOutput();

    void loadData();
    void unloadData();

    SDL_Window* mWindow;
    SDL_Renderer* mRenderer;

    bool mIsRunning;

    Uint32 mTicksCount;
};