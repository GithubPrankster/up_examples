#pragma once
typedef struct{
    float pos[2];
}me_vertex;

typedef struct{
    uint32_t VAO, VBO, EBO;
    uint32_t vert_cnt, indi_cnt;
}me_mesh;

me_mesh* me_mesh_create(me_vertex* verts, const uint32_t vcount, uint32_t* indices, const uint32_t icount);
void me_mesh_render(me_mesh* mesh);
void me_mesh_destroy(me_mesh* mesh);
