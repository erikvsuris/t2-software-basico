#include <stdio.h>
#include "mymemory.h"
#define MEMORY_SIZE 1000

int main() {
    printf("\nGERENCIADOR DE MEMÓRIA\n");

    printf("\nInicializando memória...\n");
    mymemory_t *memory = mymemory_init(MEMORY_SIZE);

    printf("\nRealizando alocações...\n");

    int v_size1 = 64;
    int *v1 = mymemory_alloc(memory, v_size1);
    for (int i = 0; i < v_size1; i++)
        v1[i] = i;

    int v_size2 = 128;
    int *v2 = mymemory_alloc(memory, v_size2);
    for (int i = 0; i < v_size2; i++)
        v2[i] = i;

   int v_size3 = 32;
    int *v3 = mymemory_alloc(memory, v_size3);
    for (int i = 0; i < v_size3; i++)
        v3[i] = i;

    mymemory_display(memory);

    printf("\nLiberando alocação...\n");
    mymemory_free(memory, v1);
    mymemory_display(memory);

    printf("\nRealizando nova alocação...\n");

    int v_size4 = 48;
    int *v4 = mymemory_alloc(memory, v_size4);
    for (int i = 0; i < v_size4; i++)
        v4[i] = i;

    mymemory_display(memory);

    printf("\nStatus da memória...\n");
    mymemory_stats(memory);

    printf("\nRelease da memória...\n");
    mymemory_release(memory);

    return 0;
}