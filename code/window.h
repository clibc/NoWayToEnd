#pragma once
#include "common.h"

struct windowgl_sdl
{
    char *name;
    unsigned int width;
    unsigned int height;
    SDL_Window *window;
};

void create_window(windowgl_sdl &window, char *name, int width, int height);
