#include "animation.h"
#include <cstring>

Animation::Animation(const char* path, int imageSizeW,
    int imageSizeH, int frameSize, int posX, int posY)
    : _renderer(Renderer::GetInstance())
    , _frame(0)
{
    _frameCount = imageSizeW / frameSize;

    _srcRectsH = new SDL_Rect[_frameCount];

    for (int i = 0; i < _frameCount; i++) {
        _srcRectsH[i] = { i * frameSize, 0, frameSize, imageSizeH };
    }

    _destRect = { posX, posY, CELLSIZE, CELLSIZE };

    SDL_RWops* file     = SDL_RWFromFile(path, "rb");
    SDL_Surface* _image = IMG_LoadPNG_RW(file);
    if (!_image)
        DEBUG("animation.cpp: IMG_Load_RW: " << IMG_GetError());

    _texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), _image);
    if (_texture == NULL)
        DEBUG("animation.cpp: Texture is NULL" << SDL_GetError);
    SDL_FreeSurface(_image);
}

void Animation::Play()
{
    SDL_Rect* currentClip = &_srcRectsH[(int)_frame];
    _renderer->RenderAnimationFrame(_texture, currentClip, &_destRect);

    // TODO: Calculate the proper value
    _frame += Time::DeltaTime() * _frameCount;
    if (_frame >= (float)_frameCount-1)
       _frame = 0;
}

void Animation::operator=(const Animation& other)
{
    _renderer   = other._renderer;
    _destRect   = other._destRect;
    _texture    = other._texture;
    _frame      = other._frame;
    _frameCount = other._frameCount;
    _srcRectsH  = new SDL_Rect[_frameCount];
    memcpy(_srcRectsH, other._srcRectsH, sizeof(SDL_Rect) * _frameCount);
}

void Animation::ChangePositionOnScreen(int x, int y)
{
    _destRect.x = x;
    _destRect.y = y;
}

Animation::~Animation()
{
    delete[] _srcRectsH;
}