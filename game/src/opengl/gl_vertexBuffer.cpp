#include "gl_vertexBuffer.h"

namespace ogl
{
    vertexBuffer::vertexBuffer(std::vector<float> &indices)
        : m_indices(&indices), m_numVertices(indices.size())
    {
        glCreateBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices, &indices[0], GL_STATIC_DRAW);
    }

    void vertexBuffer::SetVertexAttribArray(GLuint index, GLuint size, size_t stride, const GLvoid *pointer)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
        glEnableVertexAttribArray(index);
    }
};
