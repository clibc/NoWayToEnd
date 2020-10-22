#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "gameDefines.h"
#include "glm/glm.hpp"

class gl_renderer
{
public:
    void Init();
    void Render();
    void SetViewPort(float x, float y);

private:
    static gl_renderer *m_instance;
};