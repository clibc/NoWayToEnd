#include "texture.h"
#include "renderer.h"

Texture::Texture(const char *filename, int imageSizeW, int imageSizeH,
                 int spriteSizeW, int spriteSizeH, int positionX, int positionY)
{
    _srcRect.x = 0;
    _srcRect.y = 0;
    _srcRect.w = imageSizeW;
    _srcRect.h = imageSizeH;

    _destRect.x = positionX;
    _destRect.y = positionY;
    _destRect.w = spriteSizeW;
    _destRect.h = spriteSizeH;

    SDL_RWops *file = SDL_RWFromFile(filename, "rb");
    SDL_Surface *_image = IMG_LoadPNG_RW(file);
    if (!_image)
        DEBUG("texture.cpp: IMG_Load_RW: " << IMG_GetError());

    _texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), _image);
    if (_texture == NULL)
        DEBUG("Texture.cpp: Texture is NULL" << SDL_GetError);
    SDL_FreeSurface(_image);
}

Texture::Texture(const Texture &t2)
{
    _texture = t2._texture;

    _srcRect.x = t2._srcRect.x;
    _srcRect.y = t2._srcRect.y;
    _srcRect.w = t2._srcRect.w;
    _srcRect.h = t2._srcRect.h;

    _destRect.x = t2._destRect.x;
    _destRect.y = t2._destRect.y;
    _destRect.w = t2._destRect.w;
    _destRect.h = t2._destRect.h;
}

Texture::~Texture()
{
    //TODO: After we add texture to vector in Game object, we need to keep this
    // texture alive (even though we have a copy constructor)
    // Can I use shared pointer?

    //SDL_DestroyTexture(_texture);
}

void Texture::ChangePositionOnScreen(int x, int y)
{
    _destRect.x = x;
    _destRect.y = y;
}