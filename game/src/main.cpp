#include "SDL.h"
#include "game.h"

int main(int argc, char *args[])
{

    if (SDL_Init(SDL_INIT_VIDEO))
        std::cout << "Initializatin failed!"
                  << "\n";

    TTF_Init();
    IMG_Init(IMG_INIT_PNG);

    SDL_Window *window;
    window = SDL_CreateWindow("Sdl window",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIN_W, WIN_H,
                              SDL_WINDOW_SHOWN);

    Renderer renderer(window);
    Game myGame;

    myGame.Update();

    SDL_DestroyWindow(window);

    IMG_Quit();
    TTF_Quit();
    SDL_Quit();

    return 0;
}
