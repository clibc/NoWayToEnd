#include "vertexBuffer.h"

void generate_vertex_buffer(vertex_buffer &vb)
{
    glGenBuffers(1, &vb.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb.size, (float *)vb.vertices, GL_STATIC_DRAW);
}

void generate_dynamic_vertex_buffer(vertex_buffer &vb)
{
    glGenBuffers(1, &vb.bufferID);
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glBufferData(GL_ARRAY_BUFFER, vb.size, (float *)vb.vertices, GL_DYNAMIC_DRAW);
}

void set_vertex_attributef(const vertex_buffer &vb, unsigned int index, int size, int32_t stride, const void *pointer)
{
    glBindBuffer(GL_ARRAY_BUFFER, vb.bufferID);
    glEnableVertexAttribArray(index);
    glVertexAttribPointer(index, size, GL_FLOAT, GL_FALSE, stride, pointer);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void create_batch_series(batch &bch, int quadCount, int quadsPerRow)
{
    bch.quadCount = quadCount;
    bch.index_count = bch.quadCount * 6;
    bch.vertex_data = (Vertex *)malloc(sizeof(Vertex) * bch.quadCount * 4);
    bch.vertexType = VCORDTCORD;

    for (int i = 0; i < bch.quadCount; ++i)
    {
        CreateQuadBatch((Vertex *)&bch.vertex_data[i * 4], 0.0f + i % quadsPerRow, 1.0f * (i / quadsPerRow));
    }
    CreateIndexArrayBatch(bch);

    glCreateBuffers(1, &bch.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bch.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * bch.index_count, bch.index_data, GL_STATIC_DRAW);

    vertex_buffer vb;
    vb.vertices = (float *)bch.vertex_data;
    vb.size = sizeof(Vertex) * 4 * bch.quadCount;
    generate_dynamic_vertex_buffer(vb);
    bch.vertexBuffer = vb.bufferID;
    set_vertex_attributef(vb, 0, 3, sizeof(float) * 5, (void *)0);
    set_vertex_attributef(vb, 1, 2, sizeof(float) * 5, (void *)(sizeof(float) * 3));
}

void create_batch_for_level(batch &bch, level &lvl)
{
    int quad_count = 0;
    for (int i = 0; i < sizeof(lvl.cells) / sizeof(lvl.cells[0]); ++i)
        if (lvl.cells[i] == WALL)
            quad_count += 1;

    bch.quadCount = quad_count;
    bch.index_count = bch.quadCount * 6;
    bch.vertex_data = (Vertex *)malloc(sizeof(Vertex) * bch.quadCount * 4);
    bch.vertexType = VCORDTCORD;

    int count_for_quad_index = 0;
    for (int i = 0; i < sizeof(lvl.cells) / sizeof(lvl.cells[0]); ++i)
    {
        if (lvl.cells[i] == WALL)
        {
            float x = (float)(i / 10);
            float y = (float)(i % 10);
            CreateQuadBatch((Vertex *)(&bch.vertex_data[count_for_quad_index * 4]), 0.0f + x, 1.0f * y);
            count_for_quad_index += 1;
        }
    }
    CreateIndexArrayBatch(bch);

    glCreateBuffers(1, &bch.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bch.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * bch.index_count, bch.index_data, GL_STATIC_DRAW);

    vertex_buffer vb;
    vb.vertices = (float *)bch.vertex_data;
    vb.size = sizeof(Vertex) * 4 * bch.quadCount;
    generate_dynamic_vertex_buffer(vb);
    bch.vertexBuffer = vb.bufferID;
    set_vertex_attributef(vb, 0, 3, sizeof(float) * 5, (void *)0);
    set_vertex_attributef(vb, 1, 2, sizeof(float) * 5, (void *)(sizeof(float) * 3));
}

void CreateQuadBatch(Vertex *array, float x, float y)
{
    const float size = 1.0f;

    Vertex ver1 = {glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f)};
    Vertex ver2 = {glm::vec3(x + size, y, 0.0f), glm::vec2(1.0f, 0.0f)};
    Vertex ver3 = {glm::vec3(x + size, y + size, 0.0f), glm::vec2(0.0f, 0.0f)};
    Vertex ver4 = {glm::vec3(x, y + size, 0.0f), glm::vec2(0.0f, 1.0f)};

    array[0] = ver1;
    array[1] = ver2;
    array[2] = ver3;
    array[3] = ver4;
}

void CreateSeriesBatchTwoTextures(batch &bch, int quadCount, int quadsPerRow)
{
    bch.quadCount = quadCount;
    bch.index_count = bch.quadCount * 6;
    bch.vertex_data = (Vertex *)malloc(sizeof(TextureVertex) * bch.quadCount * 4);
    bch.vertexType = VCORDTCORDTINDEX;

    bool index = false;
    for (int i = 0; i < bch.quadCount; ++i)
    {
        if (index)
        {
            CreateQuadBatchTextureIndex(((TextureVertex *)bch.vertex_data) + (i * 4), 0.0f + i % quadsPerRow, 1.0f * (i / quadsPerRow), 1.0f);
            index = false;
        }
        else
        {
            CreateQuadBatchTextureIndex(((TextureVertex *)bch.vertex_data) + (i * 4), 0.0f + i % quadsPerRow, 1.0f * (i / quadsPerRow), 0.0f);
            index = true;
        }
    }
    CreateIndexArrayBatch(bch);

    glCreateBuffers(1, &bch.indexBuffer);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, bch.indexBuffer);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(int) * bch.index_count, bch.index_data, GL_STATIC_DRAW);

    vertex_buffer vb;
    vb.vertices = (float *)bch.vertex_data;
    vb.size = sizeof(TextureVertex) * 4 * bch.quadCount;
    generate_dynamic_vertex_buffer(vb);
    bch.vertexBuffer = vb.bufferID;
    set_vertex_attributef(vb, 0, 3, sizeof(float) * 6, (void *)0);
    set_vertex_attributef(vb, 1, 2, sizeof(float) * 6, (void *)(sizeof(float) * 3));
    set_vertex_attributef(vb, 2, 1, sizeof(float) * 6, (void *)(sizeof(float) * 5));
}

void CreateQuadBatchTextureIndex(TextureVertex *array, float x, float y, float textureID)
{
    const float size = 1.0f;

    TextureVertex ver1 = {glm::vec3(x, y, 0.0f), glm::vec2(1.0f, 1.0f), textureID};
    TextureVertex ver2 = {glm::vec3(x + size, y, 0.0f), glm::vec2(1.0f, 0.0f), textureID};
    TextureVertex ver3 = {glm::vec3(x + size, y + size, 0.0f), glm::vec2(0.0f, 0.0f), textureID};
    TextureVertex ver4 = {glm::vec3(x, y + size, 0.0f), glm::vec2(0.0f, 1.0f), textureID};

    array[0] = ver1;
    array[1] = ver2;
    array[2] = ver3;
    array[3] = ver4;
}

void CreateIndexArrayBatch(batch &bat)
{
    int *indices = (int *)malloc(sizeof(int) * bat.quadCount * 6);
    int count = 0;
    for (int i = 0; i < bat.quadCount; ++i)
    {
        int index = i * 6;
        indices[index] = count;
        indices[index + 1] = count + 1;
        indices[index + 2] = count + 2;
        indices[index + 3] = count + 2;
        indices[index + 4] = count + 3;
        indices[index + 5] = count;
        count += 4;
    }
    bat.index_data = indices;
}
