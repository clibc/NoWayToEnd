#include "common.h"
#include "shader.h"
#include "vertexBuffer.h"

struct scene
{
    shader sh;
    vertex_buffer vb;
    glm::mat4 view;
    glm::mat4 projection;
};

void scene_init(scene &scn);
