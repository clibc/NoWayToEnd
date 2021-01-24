#pragma once
#include "common.h"

struct shader
{
    GLuint programID;
};

void create_shader(shader &sh, const char *vs, const char *fs);
GLuint load_shader(const char *vs, const char *fs);
GLint get_uniform_location(shader &shdr, const char *name);
bool set_uniform_mat4(shader &shdr, const char *name, const glm::mat4 &matrix);
bool set_uniform_vec2(shader &shdr, const char *name, const glm::vec2 &vector);
bool set_uniform_vec3(shader &shdr, const char *name, const glm::vec3 &vector);
shader load_default_shader();
inline void shader_bind(shader sh) { glUseProgram(sh.programID); }
