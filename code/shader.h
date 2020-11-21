#pragma once
#include "common.h"

struct shader
{
    GLuint programID;
};

void CreateShader(shader &sh, const char *vs, const char *fs);
GLuint LoadShader(const char *vs, const char *fs);
GLint GetUniformLocation(shader &shdr, const char *name);
bool SetUniformMat4(shader &shdr, const char *name, const glm::mat4 &matrix);
