#pragma once
#include "texture.h"
#include "SDL_ttf.h"

// TTF_Init() should be already called

#define USEDFONT "../fonts/calibrii.ttf"

class Text : public Texture
{
public:
    Text(const char *text, SDL_Color color, int size, int posX, int posY);
    Text(const Text &text1);
    void ChangeContext(const char *text);
    Text() = default;
    ~Text();

private:
    TTF_Font *_font;
    SDL_Color _color;
    SDL_Surface *_surface;
};
