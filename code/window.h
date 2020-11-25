#pragma once
#include "common.h"

struct windowgl_sdl
{
    // NOTE(62bit): Specify these before passing to function (CreateWindow)
    char *name;
    unsigned int width;
    unsigned int height;
    //

    SDL_Window *window;
};

void create_window(windowgl_sdl &window);
