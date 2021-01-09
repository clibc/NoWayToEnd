#include "scene.h"

void scene_init(scene &scn)
{
    create_shader(scn.anim_shader, "../code/shaders/vertex.vs", "../code/shaders/fragment.vs");
    create_shader(scn.reg_shader, "../code/shaders/regular.vs", "../code/shaders/fragment.vs");

    static float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    static float vertices_reg[] = {
        0.5f, 0.5f, 0.0f, 1.0f, 1.0f,
        0.5f, -0.5f, 0.0f, 1.0f, 0.0f,
        -0.5f, -0.5f, 0.0f, 0.0f, 0.0f,
        -0.5f, 0.5f, 0.0f, 0.0f, 1.0f};

    scn.anim_vertex.vertices = &vertices[0];
    scn.anim_vertex.size = sizeof(vertices);
    generate_dynamic_vertex_buffer(scn.anim_vertex);
    set_vertex_attributef(scn.anim_vertex, 0, 3, 3 * sizeof(float), (void *)0);

    scn.reg_vertex.vertices = &vertices_reg[0];
    scn.reg_vertex.size = sizeof(vertices_reg);
    generate_dynamic_vertex_buffer(scn.reg_vertex);
    set_vertex_attributef(scn.reg_vertex, 0, 3, 5 * sizeof(float), (void *)0);
    set_vertex_attributef(scn.reg_vertex, 1, 2, 5 * sizeof(float), (void *)(3 * sizeof(float)));

    scn.projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    set_uniform_mat4(scn.anim_shader, "projection", scn.projection);
    set_uniform_mat4(scn.reg_shader, "projection", scn.projection);

    glm::vec3 vertxPos1(0.5f, 0.5f, 0.0f);
    glm::vec3 vertxPos2(0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos3(-0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos4(-0.5f, 0.5f, 0.0f);

    set_uniform_vec3(scn.anim_shader, "c_positions[0]", vertxPos1);
    set_uniform_vec3(scn.anim_shader, "c_positions[1]", vertxPos2);
    set_uniform_vec3(scn.anim_shader, "c_positions[2]", vertxPos3);
    set_uniform_vec3(scn.anim_shader, "c_positions[3]", vertxPos4);
}
