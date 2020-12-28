#pragma once
#include <iostream>
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "SDL.h"

#define WINDOW_WIDTH 800
#define WINDOW_HEIGHT 800

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

static float delta_time;
static float first_time;

static void update_time()
{
    // TODO(62bit): FIX THIS SHIT!
    float time = (float)SDL_GetTicks();
    delta_time = time - first_time;
    first_time = time;
}
