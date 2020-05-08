#include <glad/glad.h>
#include "window.h"

me_window* win;

static void GLAPIENTRY MessageCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if (severity != GL_DEBUG_SEVERITY_NOTIFICATION)
    {
        fprintf(stderr, "%s\n", message);
    }
}

int me_init_window(const char* name, uint32_t w, uint32_t h)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        fprintf(stderr, "[SDL2]: %d\n", SDL_GetError());
        return 0;
    }

    win = malloc(sizeof(me_window));
    if(!win){
        fprintf(stderr, "[MONROE]: Could not allocate window data.\n");
        SDL_Quit();
        return 0;
    }
    win->width = w;
    win->height = h;

    SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 4);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 6);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);
    SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
    SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);
    win->window = SDL_CreateWindow(name, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, w, h, SDL_WINDOW_SHOWN | SDL_WINDOW_OPENGL | SDL_WINDOW_ALWAYS_ON_TOP);
    if(!win->window){
        fprintf(stderr, "[SDL2]: %d\n", SDL_GetError());
        SDL_Quit();
        return 0;
    }

    win->ctx = SDL_GL_CreateContext(win->window);
    if(!win->ctx){
        fprintf(stderr, "[SDL2]: %d\n", SDL_GetError());
        SDL_DestroyWindow(win->window);
        SDL_Quit();
        return 0;
    }

    if(!gladLoadGLLoader((GLADloadproc) SDL_GL_GetProcAddress)){
        fprintf(stderr, "[SDL2]: %d\n", SDL_GetError());
        SDL_GL_DeleteContext(win->ctx);
        SDL_DestroyWindow(win->window);
        SDL_Quit();
        return 0;
    }

    SDL_GL_SetSwapInterval(0);

    glViewport(0, 0, w, h);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glDebugMessageCallback(MessageCallback, 0);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glEnable(GL_DEBUG_OUTPUT);

    return 1;
}

void me_destroy_window(void)
{
    SDL_GL_DeleteContext(win->ctx);
    SDL_DestroyWindow(win->window);
    SDL_Quit();
}
