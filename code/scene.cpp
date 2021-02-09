#include "scene.h"

void scene_init(scene &scn)
{
    create_shader(scn.reg_shader, "../code/shaders/vertex.vs", "../code/shaders/fragment.vs");
    create_shader(scn.anim_shader, "../code/shaders/animation.vs", "../code/shaders/fragment.vs");

    load_level(scn.lvl, "../assets/levels/level1.lvl");
    create_batch_for_level(scn.bch, scn.lvl);

    auto projection = glm::ortho(0.0f, (float)WINDOW_WIDTH, (float)WINDOW_HEIGHT, 0.0f, -1.0f, 1.0f);
    scn.batch_model = glm::translate(glm::mat4(1.0f), glm::vec3(400.0f, 0.0f, 0.0f));
    scn.batch_model = glm::rotate(scn.batch_model, glm::radians(90.0f), glm::vec3(0.0f, 0.0f, 1.0f));
    scn.batch_model = glm::rotate(scn.batch_model, glm::radians(180.0f), glm::vec3(1.0f, 0.0f, 0.0f));
    scn.batch_model = glm::scale(scn.batch_model, glm::vec3(40.0f));

    scn.projection = projection;

    set_uniform_mat4(scn.reg_shader, "model", scn.batch_model);
    set_uniform_mat4(scn.reg_shader, "projection", scn.projection);

    // NOTE(62bit): animation initialize

    static float vertices[] = {
        0.5f, 0.5f, 0.0f,
        0.5f, -0.5f, 0.0f,
        -0.5f, -0.5f, 0.0f,
        -0.5f, 0.5f, 0.0f};

    scn.anim_vertex.vertices = &vertices[0];
    scn.anim_vertex.size = sizeof(vertices);
    generate_dynamic_vertex_buffer(scn.anim_vertex);
    bind_vertex_buffer(scn.anim_vertex);
    set_vertex_attributef(scn.anim_vertex, 0, 3, 3 * sizeof(float), (void *)0);

    glm::vec3 vertxPos1(0.5f, 0.5f, 0.0f);
    glm::vec3 vertxPos2(0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos3(-0.5f, -0.5f, 0.0f);
    glm::vec3 vertxPos4(-0.5f, 0.5f, 0.0f);

    set_uniform_vec3(scn.anim_shader, "c_positions[0]", vertxPos1);
    set_uniform_vec3(scn.anim_shader, "c_positions[1]", vertxPos2);
    set_uniform_vec3(scn.anim_shader, "c_positions[2]", vertxPos3);
    set_uniform_vec3(scn.anim_shader, "c_positions[3]", vertxPos4);
    set_uniform_mat4(scn.anim_shader, "projection", scn.projection);

    scn.reg_vertex.vertices = &vertices[0];
    scn.reg_vertex.size = sizeof(vertices);
    generate_dynamic_vertex_buffer(scn.reg_vertex);
    bind_vertex_buffer(scn.reg_vertex);
    set_vertex_attributef(scn.reg_vertex, 0, 3, 3 * sizeof(float), (void *)0);

    for (int i = 0; i < 100; ++i)
        if (scn.lvl.cells[i] == PLAYER)
        {
            int row = 0;
            int column = 0;
            row = i / COLUMNCOUNT;
            column = i % ROWCOUNT;
            scn.playr.x = row;
            scn.playr.y = column;
        }
}
