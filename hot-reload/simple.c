#include <libtcc.h>
#include <stdio.h>
#include <stdlib.h>

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

int main(void)
{
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

    tcc_relocate(state, TCC_RELOCATE_AUTO);

    void(*const foo)() = tcc_get_symbol(state, "foo");
    foo();
   
    tcc_delete(state);
    return 0;
}