#pragma once
#include "common.h"
#include "player.h"
#include "shader.h"
#include "vertexBuffer.h"

struct scene
{
    level lvl;
    batch bch;
    player playr;

    shader anim_shader;
    shader reg_shader;
    glm::mat4 view;
    glm::mat4 projection;
    glm::mat4 batch_model;

    vertex_buffer anim_vertex;
    vertex_buffer reg_vertex;
};

void scene_init(scene &scn);
