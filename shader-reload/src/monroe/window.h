#pragma once
#include <SDL2/SDL.h>

typedef struct{
    SDL_Window* window;
    SDL_GLContext ctx;
    uint32_t width, height;
}me_window;

extern me_window* win;

int me_init_window(const char* name, uint32_t w, uint32_t h);
void me_destroy_window(void);