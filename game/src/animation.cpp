#include "animation.h"

Animation::Animation(const char *path, int imageSizeW,
                     int imageSizeH, int frameSize, int posX, int posY)
    : _renderer(Renderer::GetInstance()), _frame(0)
{
    // TODO: CHANGE THESE DECLARATIONS
    // SOME NOOBIE PROBLEMS :)

    _srcRects[0] = {12, 0, 151, 170};
    _srcRects[1] = {391, 0, 151, 170};
    _srcRects[2] = {596, 0, 151, 170};
    _srcRects[3] = {802, 0, 151, 170};
    _srcRects[4] = {1000, 0, 151, 170};

    _destRect = {posX, posY, 80, 80};

    SDL_RWops *file = SDL_RWFromFile(path, "rb");
    SDL_Surface *_image = IMG_LoadPNG_RW(file);
    if (!_image)
        DEBUG("animation.cpp: IMG_Load_RW: " << IMG_GetError());

    _texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), _image);
    if (_texture == NULL)
        DEBUG("animation.cpp: Texture is NULL" << SDL_GetError);
    SDL_FreeSurface(_image);
}

void Animation::Play()
{
    // TODO: Count deltaTime instead of dividing by const integer.
    SDL_Rect *currentClip = &_srcRects[_frame / ANIMDELAY];

    _renderer->RenderAnimationFrame(_texture, currentClip, &_destRect);

    _frame++;
    if (_frame / ANIMDELAY >= FRAMECOUNT)
        _frame = 0;
}

Animation::~Animation() {}