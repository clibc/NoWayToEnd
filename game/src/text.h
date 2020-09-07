#pragma once
#include "texture.h"
#include "SDL_ttf.h"

// TTF_Init() should be already called

#define WORDSIZEX 16
#define WORDSIZEY 20

#define USEDFONT "../fonts/calibrii.ttf"

class Text : public Texture
{
public:
    Text(char *text, SDL_Color color, int size, int posX, int posY);
    Text(const Text &text1);
    Text() = default;
    ~Text();

private:
    char *_text;
    TTF_Font *_font;
    SDL_Color _color;
    SDL_Surface *_surface;
};
