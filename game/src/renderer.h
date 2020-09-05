#pragma once
#include "SDL.h"
#include "utils.h"
#include "gameDefines.h"
#include "texture.h"

class Renderer
{
public:
    Renderer(SDL_Window *window);
    static inline SDL_Renderer *GetRenderer() { return _renderer; }
    static inline Renderer *GetInstance() { return _instance; }
    void Begin();
    void DrawLine(const Line &line, const DrawColor &color);
    void DrawLine(const Line &line);
    void RenderBackground(const DrawColor &color);
    void RenderBackground();
    void RenderTexture(const Texture *texture);
    void End();

private:
    static SDL_Renderer *_renderer;
    static Renderer *_instance;
    SDL_Window *_window;
    DrawColor _drawColor;
    DrawColor _bgColor;
};
