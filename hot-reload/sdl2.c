#include <SDL2/SDL.h>
#include <libtcc.h>
#include <sys/stat.h>
#include <time.h>

char* up_file(const char* path)
{
    FILE* fp = fopen(path, "r");

    fseek(fp, 0, SEEK_END);
    size_t sz = ftell(fp);
    rewind(fp);
    
    char *buf = calloc(sizeof(char), sz);
    
    fread(buf, sz, sizeof(char), fp);

    fclose(fp);
    return buf;
}

int main(int argc, char** argv)
{
    if(SDL_Init(SDL_INIT_EVERYTHING) < 0){
        fprintf(stderr, "[SDL2]: %s\n", SDL_GetError());
        return -1;
    }
    SDL_Window* window = SDL_CreateWindow("SDL2 Example", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_SHOWN | SDL_WINDOW_ALWAYS_ON_TOP);
    if(!window){
        fprintf(stderr, "[SDL2]: %s\n", SDL_GetError());
        SDL_Quit();
        return -1;
    }

    SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    if(!renderer){
        fprintf(stderr, "[SDL2]: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return -1;
    }

    TCCState* state = tcc_new();
    if(!state){
        fprintf(stderr, "[TYPE DEV]: Could not initialize TCCState.\n");
        return -1;
    }

    char* file = up_file("test.c");
    tcc_set_output_type(state, TCC_OUTPUT_MEMORY);
    if(tcc_compile_string(state, file) < 0){
        fprintf(stderr, "[TYPE DEV]: Could not comple file.\n");
        free(file);
        tcc_delete(state);
        return -1;
    }
    free(file);

    time_t timer;
    struct stat stats;
    stat("test.c", &stats);
    timer = stats.st_mtime;

    tcc_relocate(state, TCC_RELOCATE_AUTO);

    void(*foo)() = tcc_get_symbol(state, "foo");

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

        stat("test.c", &stats);
        if(difftime(stats.st_mtime, timer) != 0){
            timer = stats.st_mtime;
            file = up_file("test.c");

            tcc_delete(state);
            state = tcc_new();

            tcc_set_output_type(state, TCC_OUTPUT_MEMORY);
            tcc_compile_string(state, file);

            free(file);

            tcc_relocate(state, TCC_RELOCATE_AUTO);
            foo = tcc_get_symbol(state, "foo");
        }

        if(cur_keyboard[SDL_SCANCODE_A]){
            foo();
        }

        SDL_RenderClear(renderer);

        SDL_RenderPresent(renderer);
        SDL_Delay(60);
    }   

    tcc_delete(state);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}