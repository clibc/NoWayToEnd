#pragma once
#include "GL/glew.h"
#include "common.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <vector>

struct shader
{
    const char *path;
    GLuint programID;
};

GLuint LoadShader(const char *vs, const char *fs);
shader CreateShader(const char *vs, const char *fs);
