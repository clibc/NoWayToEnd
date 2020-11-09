#include "SDL.h"
#include "game.h"
#include "opengl/gl_renderer.h"

int main(int argc, char *args[])
{

    if (SDL_Init(SDL_INIT_EVERYTHING))
        std::cout << "Initializatin failed!"
                  << "\n";
    SDL_Window *window;
    window = SDL_CreateWindow("NWTE",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIN_W, WIN_H,
                              SDL_WINDOW_OPENGL);

    SDL_GL_CreateContext(window);

    DEBUG("init");

    ogl::renderer renderer(window);
    Game game;
    game.Run();

    SDL_DestroyWindow(window);

    SDL_Quit();

    return 0;
}
