#include <glad/glad.h>
#include <stdlib.h>
#include <stdio.h>
#include "mesh.h"

me_mesh* me_mesh_create(me_vertex* verts, const uint32_t vcount, uint32_t* indices, const uint32_t icount)
{
    me_mesh* mesh = malloc(sizeof(me_mesh));
    if(!mesh){
        fprintf(stderr, "[MONROE]: Could not allocate memory for a mesh!\n");
        return NULL;
    }

    mesh->vert_cnt = vcount;
    mesh->indi_cnt = icount;
    glGenVertexArrays(1, &mesh->VAO);
    glGenBuffers(1, &mesh->VBO);
    glGenBuffers(1, &mesh->EBO);

    glBindVertexArray(mesh->VAO);

    glBindBuffer(GL_ARRAY_BUFFER, mesh->VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(me_vertex) * mesh->vert_cnt, &verts[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh->EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(uint32_t) * mesh->indi_cnt, indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(me_vertex), NULL);
    glEnableVertexAttribArray(0);

    glBindVertexArray(0);

    return mesh;
}

void me_mesh_render(me_mesh* mesh)
{
    glBindVertexArray(mesh->VAO);
    glDrawElements(GL_TRIANGLES, mesh->indi_cnt, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void me_mesh_destroy(me_mesh* mesh)
{
    glDeleteVertexArrays(1, &mesh->VAO);
    glDeleteBuffers(1, &mesh->EBO);
    glDeleteBuffers(1, &mesh->VBO);

    free(mesh);
}
