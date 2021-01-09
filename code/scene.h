#include "common.h"
#include "shader.h"
#include "vertexBuffer.h"

struct scene
{
    shader anim_shader;
    shader reg_shader;
    vertex_buffer anim_vertex;
    vertex_buffer reg_vertex;
    glm::mat4 view;
    glm::mat4 projection;
};

void scene_init(scene &scn);
