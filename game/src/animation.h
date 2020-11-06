#pragma once
#include "renderer.h"
#include "time.h"
#include <cstring>

#define FRAMECOUNT 5
#define ANIMDELAY 50
#define FPS 60

class Animation
{
public:
    Animation() = default;
    Animation(const char *path, int imageSizeW, int imageSizeH,
              int frameSize, int posX, int posY);
    void operator=(const Animation &other);
    void ChangePositionOnScreen(int x, int y);
    ~Animation();
    void Play();

private:
    Renderer *_renderer;
    SDL_Rect *_srcRectsH;
    SDL_Rect _destRect;
    SDL_Texture *_texture;

    float _frame;
    int _frameCount;
};
