#pragma once
#include "common.h"
#include "level_loader.h"

struct vertex_buffer
{
    // NOTE(62bit): bufferPointer and size must be specified
    // when passing this to GenerateVertexBuffer function.
    // And function will create buffer and initialize bufferID.
    float *vertices;
    size_t size;
    unsigned int bufferID;
};

struct Vertex
{
    glm::vec3 positions;
    glm::vec2 textureCoords;
};

struct TextureVertex
{
    glm::vec3 positions;
    glm::vec2 textureCoords;
    float textureID;
};

enum VertexAttribType
{
    VCORDTCORDTINDEX,
    VCORDTCORD,
    VCORD
};

struct batch
{
    Vertex *vertex_data;
    int *index_data;
    GLuint indexBuffer;
    GLuint vertexBuffer;
    int quadCount;
    int index_count;
    VertexAttribType vertexType;
};

void generate_vertex_buffer(vertex_buffer &vb);
void generate_dynamic_vertex_buffer(vertex_buffer &vb);
inline void set_vertex_attributef(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer);
inline void bind_vertex_buffer(const vertex_buffer &vb) { glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID); }
inline void bind_vertex_buffer_id(GLuint vb) { glBindBuffer(GL_ARRAY_BUFFER, vb); }

void create_batch_series(batch &bch, int quadCount, int quadsPerRow);
void create_batch_for_level(batch &bch, level &lvl);
void CreateQuadBatch(Vertex *array, float x, float y);
void CreateIndexArrayBatch(batch &bat);
void CreateQuadBatchTextureIndex(TextureVertex *array, float x, float y, float textureID);
void CreateSeriesBatchTwoTextures(batch &bch, int quadCount, int quadsPerRow);
