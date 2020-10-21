#pragma once
#include "GL/glew.h"
#include "SDL.h"
#include "gameDefines.h"
#include "glm/glm.hpp"

class gl_renderer
{
public:
    void Init();
    void Render(); //take the shader and VB as parameters

private:
    static gl_renderer *m_instance;
};