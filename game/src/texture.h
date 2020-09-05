#pragma once
#include "SDL_image.h"
#include "utils.h"

class Texture
{
public:
    SDL_Rect _srcRect;
    SDL_Rect _destRect;

    Texture() = default;
    Texture(const char *filepath, int imageSizeW, int imageSizeH,
            int spriteSizeW, int spriteSizeH, int positionX = 0, int positionY = 0);
    Texture(const Texture &t2);
    void ChangePositionOnScreen(int x, int y);
    inline SDL_Texture *GetTexture() const { return _texture; }
    ~Texture();

private:
    SDL_Texture *_texture;
};
