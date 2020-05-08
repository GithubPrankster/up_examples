#include "monroe/window.h"
#include "monroe/shader.h"
#include "monroe/mesh.h"

#include <glad/glad.h>
#include <time.h>
#include <sys/stat.h>

static long mod_time(const char* file)
{
    struct stat stats;
    stat(file, &stats);
    return stats.st_mtime;
}

int main(int argc, char** argv)
{
    me_init_window("Shader Reloading", 640, 480);

    me_vertex verts[] = {
        (me_vertex){
            .pos = {1.0f, 1.0f}
        },
        (me_vertex){
            .pos = {1.0f, -1.0f}
        },
        (me_vertex){
            .pos = {-1.0f, -1.0f}
        },
        (me_vertex){
            .pos = {-1.0f, 1.0f}
        }    
    };

    uint32_t indices[] = {
        0, 1, 3,
        1, 2, 3
    }; 

    me_mesh *tri = me_mesh_create(verts, 4, indices, 6);

    long mtimer = mod_time("shaders/basic.fs");
    unsigned int program = me_shader_create("shaders/basic.vs", "shaders/basic.fs");
    glUseProgram(program);

    glClearColor(0.1, 0.1, 0.1, 1.0);
    int quitter = 0;
    SDL_Event e;
    while(!quitter){
        while(SDL_PollEvent(&e)) {
            if(e.type == SDL_QUIT) {
                quitter = 1;
            }
        }

        const Uint8* cur_keyboard = SDL_GetKeyboardState(NULL);
        if(cur_keyboard[SDL_SCANCODE_ESCAPE]){
            quitter = 1;
        }

        long ntime = mod_time("shaders/basic.fs");
        if(difftime(ntime, mtimer) != 0){
            printf("Change detected!!\n");
            mtimer = ntime;
            glDeleteProgram(program);
            program = me_shader_create("shaders/basic.vs", "shaders/basic.fs");
        }

        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(program);
        me_shader_float(program, "time", (float)SDL_GetTicks());
        float res[] = {win->width, win->height};
        me_shader_vec2(program, "res", res);
        me_mesh_render(tri);

        SDL_GL_SwapWindow(win->window);
    }
    me_mesh_destroy(tri);
    glDeleteProgram(program);
    me_destroy_window();
    return 0;
}
