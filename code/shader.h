#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
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

shader CreateShader(const char *vs, const char *fs);
GLuint LoadShader(const char *vs, const char *fs);
GLint GetUniformLocation(shader &shdr, const char *name);
bool SetUniformMat4(shader &shdr, const char *name, const glm::mat4 &matrix);
