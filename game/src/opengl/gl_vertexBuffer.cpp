#include "gl_vertexBuffer.h"

namespace ogl
{
    vertexBuffer::vertexBuffer(std::vector<float> &indices)
        : m_numVertices(indices.size()), m_indices(indices)
    {

        glCreateBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices, &indices.front(), GL_STATIC_DRAW);
    }

    vertexBuffer::vertexBuffer(float *indices, int size)
        : m_numVertices(size), m_posArray(indices)
    {

        glCreateBuffers(1, &m_bufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glBufferData(GL_ARRAY_BUFFER, m_numVertices, indices, GL_STATIC_DRAW);
    }

    void vertexBuffer::SetVertexAttribArray(GLuint index, GLuint size, size_t stride, const GLvoid *pointer)
    {

        // NOTE(62bit): 'stride' Specifies the byte offset between consecutive
        // generic vertex attributes
        // 'pointer' Specifies a offset of the first component of the first
        // generic vertex attribute
        // Considered my conventions vertex attribute is one line of the array
        // and components are the vertex position and texture coordinates (or vertex  colors)

        glEnableVertexAttribArray(index);
        glBindBuffer(GL_ARRAY_BUFFER, m_bufferID);
        glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    }
}; // namespace ogl
