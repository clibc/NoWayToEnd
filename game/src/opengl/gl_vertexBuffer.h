#pragma once
#include "gl/glew.h"
#include "glm/glm.hpp"
#include "glm/gtc/type_ptr.hpp"
#include <vector>

namespace ogl
{
    class vertexBuffer
    {
    public:
        vertexBuffer() = default;
        vertexBuffer(std::vector<float> &indices);
        vertexBuffer(float *indices, int size);
        void SetVertexAttribArray(GLuint index, GLuint size, size_t stride, const GLvoid *pointer);
        const void inline Bind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); }
        void inline Unbind() { glBindBuffer(GL_ARRAY_BUFFER, m_bufferID); };

        int32_t m_numVertices;

    private:
        GLuint m_bufferID;
        std::vector<float> m_indices;
        float *m_posArray;
    };
}; // namespace ogl
