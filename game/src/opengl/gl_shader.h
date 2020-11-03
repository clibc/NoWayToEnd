#pragma once
#include "GL/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include "opengl/loadShaders.hpp"

namespace ogl
{
    class shader
    {
        public:
        shader() = default;
        shader(const char *vsPath, const char *fsPath);
        inline void Bind() { glUseProgram(m_shaderProgram); }
        void ChangeUniformMatrix(GLint location, glm::mat4 matrix);
        void SetUniform1f(const char *name, float value);
        void SetUniform3fv(const char *name, glm::vec3 vector);
        inline GLint GetUniformLocation(const char *name) { return glGetUniformLocation(m_shaderProgram, name); }
        inline GLuint GetProgram() { return m_shaderProgram; }
        
        private:
        GLuint m_shaderProgram;
    };
}; // namespace ogl
