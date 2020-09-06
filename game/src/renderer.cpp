#include "renderer.h"

SDL_Renderer *Renderer::_renderer = 0;
Renderer *Renderer::_instance;

Renderer::Renderer(SDL_Window *window)
    : _window(window)
{
    Renderer::_renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    Renderer::_instance = this;
    {
        _drawColor._r = 0;
        _drawColor._g = 255;
        _drawColor._b = 0;
    }

    {
        _bgColor._r = 0;
        _bgColor._g = 0;
        _bgColor._b = 0;
    }
}

void Renderer::Begin()
{
    SDL_RenderClear(_renderer);
}

void Renderer::DrawLine(const Line &line, const DrawColor &color)
{
    SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_renderer, line._x1, line._y1, line._x2, line._y2);
    SDL_SetRenderDrawColor(_renderer, _bgColor._r, _bgColor._g, _bgColor._b, SDL_ALPHA_OPAQUE);
}

void Renderer::DrawLine(const Line &line)
{
    SDL_SetRenderDrawColor(_renderer, _drawColor._r, _drawColor._g, _drawColor._b, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawLine(_renderer, line._x1, line._y1, line._x2, line._y2);
    SDL_SetRenderDrawColor(_renderer, _bgColor._r, _bgColor._g, _bgColor._b, SDL_ALPHA_OPAQUE);
}

void Renderer::RenderBackground(const DrawColor &color)
{
    SDL_SetRenderDrawColor(_renderer, color._r, color._g, color._b, SDL_ALPHA_OPAQUE);
    SDL_RenderClear(_renderer);
}

void Renderer::RenderBackground()
{
    SDL_RenderClear(_renderer);
    SDL_SetRenderDrawColor(_renderer, _bgColor._r, _bgColor._g, _bgColor._b, SDL_ALPHA_OPAQUE);
}

void Renderer::RenderTexture(const Texture *texture)
{
    if (SDL_RenderCopy(_renderer, texture->GetTexture(), &texture->_srcRect, &texture->_destRect))
        DEBUG(SDL_GetError());
}

void Renderer::End()
{
    SDL_RenderPresent(_renderer);
}