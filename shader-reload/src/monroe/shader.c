#include <glad/glad.h>
#include <stdio.h>
#include <stdlib.h>
#include "shader.h"

const char* up_file(const char* file)
{
    FILE *fp = fopen(file, "r");
    if(!fp){
        printf("[MONROE]: Could not open file.\n");
        return NULL;
    }
    fseek(fp, 0, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);

    char *buffer = calloc(sizeof(char), sz + 1);
    if(!buffer){
        printf("[MONROE]: Could not create storage for file.\n");
        return NULL;
    }

    fread(buffer, sz, sizeof(char), fp);
    fclose(fp);
    return buffer;
}

unsigned int me_shader_create(const char* vsrc, const char* fsrc)
{
    const char* vert = up_file(vsrc);
    const char* frag = up_file(fsrc);

    unsigned int vertex = glCreateShader(GL_VERTEX_SHADER);
    unsigned int fragment = glCreateShader(GL_FRAGMENT_SHADER);
    unsigned int prog = glCreateProgram();

    glShaderSource(vertex, 1, &vert, NULL);
    glCompileShader(vertex);

    glShaderSource(fragment, 1, &frag, NULL);
    glCompileShader(fragment);

    glAttachShader(prog, vertex);
    glAttachShader(prog, fragment);
    glLinkProgram(prog);

    glDeleteShader(fragment);
    glDeleteShader(vertex);
    return prog;
}