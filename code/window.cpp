#include "window.h"

void create_window(windowgl_sdl &window, char *name, int width, int height)
{
    SDL_Init(SDL_INIT_EVERYTHING);

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 16);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

    char *temp = (char *)malloc(strlen(name));
    strcpy(temp, name);

    window.name = temp;
    window.width = width;
    window.height = height;
    window.window = SDL_CreateWindow(window.name,
                                     SDL_WINDOWPOS_CENTERED,
                                     SDL_WINDOWPOS_CENTERED,
                                     window.width,
                                     window.height,
                                     SDL_WINDOW_OPENGL);
    SDL_GL_CreateContext(window.window);

    SetAttribs();

    GLenum error = glewInit();
    if (error != GLEW_OK)
    {
        printf("%s", glewGetErrorString(error));
        exit(1);
    }

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
}
