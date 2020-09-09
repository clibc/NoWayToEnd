#include "text.h"
#include "renderer.h"

Text::Text(const char *text, SDL_Color color, int size, int posX, int posY)
    : _color(color)
{
    _destRect.x = posX;
    _destRect.y = posY;

    _font = TTF_OpenFont(USEDFONT, size);
    _surface = TTF_RenderText_Solid(_font, text, color);

    _texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), _surface);
    if (_texture == NULL)
        DEBUG("Text.cpp: Texture is NULL" << SDL_GetError);

    SDL_QueryTexture(_texture, NULL, NULL, &_destRect.w, &_destRect.h);
}

Text::Text(const Text &text1)
{
    _font = text1._font;
    _color = text1._color;
    _texture = text1._texture;
}

void Text::ChangeContext(const char *text)
{
    _surface = TTF_RenderText_Solid(_font, text, _color);
    _texture = SDL_CreateTextureFromSurface(Renderer::GetRenderer(), _surface);
    SDL_QueryTexture(_texture, NULL, NULL, &_destRect.w, &_destRect.h);
}

Text::~Text()
{
    // We probably will need these to create a new texture when the text context changes,
    // rather than reopenning two new streams in runtime.
    //TTF_CloseFont(_font);
    //SDL_FreeSurface(_surface);
}