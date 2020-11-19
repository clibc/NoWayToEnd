#pragma once
#include <iostream>

#define WINDOW_WIDTH 600
#define WINDOW_HEIGHT 600

#define debug(x) std::cout << x << '\n'

#define SetAttribs()                                                               \
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);                                   \
    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);                             \
    SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);                                       \
    SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);                                     \
    SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);                                      \
    SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE, 8);                                     \
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);                          \
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);                          \
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE); \
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
