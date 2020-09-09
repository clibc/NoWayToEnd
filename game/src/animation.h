#pragma once
#include "renderer.h"

#define FRAMECOUNT 5
#define ANIMDELAY 50

class Animation
{
public:
    Animation() = default;
    Animation(const char *path, int imageSizeW, int imageSizeH,
              int frameSize, int posX, int posY);
    ~Animation();
    void Play();

private:
    Renderer *_renderer;
    SDL_Rect _srcRects[FRAMECOUNT];
    SDL_Rect _destRects[FRAMECOUNT];
    SDL_Texture *_texture;

    int _frame;
};
