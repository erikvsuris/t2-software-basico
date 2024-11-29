#include <stdlib.h>
#include "mymemory.h"

mymemory_t* mymemory_init(size_t size) {
    if (size <= 0) return NULL;

    mymemory_t *memory = (mymemory_t*) malloc(sizeof(mymemory_t));
    if (memory == NULL) return NULL;

    memory->pool = malloc(size);
    if (memory->pool == NULL) {
        free(memory);
        return NULL;
    }
    
    memory->total_size = size;
    memory->head = NULL;

    return memory;
}

void* mymemory_alloc(mymemory_t *memory, size_t size) {
    if (size <= 0 || size > memory->total_size) return NULL;

    size_t free_memory = memory->total_size;
    allocation_t *current_allocation = memory->head;

    while (current_allocation != NULL) {
        free_memory -= current_allocation->size;
        current_allocation = current_allocation->next;
    }

    if (size > free_memory) return NULL;

    allocation_t *allocation = (allocation_t*) malloc(sizeof(allocation_t));
    if (allocation == NULL) return NULL;

    allocation->size = size;
    allocation->next = NULL;

    void *allocation_start = memory->pool;
    current_allocation = memory->head;

    while (current_allocation != NULL) {
        if (current_allocation->next == NULL) {
            allocation_start = current_allocation->start + current_allocation->size;
            current_allocation->next = allocation;
            break;
        }
        if (size <= (size_t) (memory->head->start - memory->pool)) {
            allocation_start = memory->pool;
            allocation->next = memory->head;
            memory->head = allocation;
            break;
        }
        if (size <= (size_t) (current_allocation->next->start - (current_allocation->start + current_allocation->size))) {
            allocation_start = current_allocation->start + current_allocation->size;
            allocation->next = current_allocation->next;
            current_allocation->next = allocation;
            break;
        }
        current_allocation = current_allocation->next;
    }

    if (memory->head == NULL) memory->head = allocation;
    allocation->start = allocation_start;

    return allocation->start;
}

void mymemory_free(mymemory_t *memory, void *ptr) {
    if (memory == NULL || ptr == NULL) return;

    allocation_t *current_allocation = memory->head;
    allocation_t *previous_allocation = NULL;
    while (current_allocation != NULL) {
        if (current_allocation->start == ptr) {
            if (previous_allocation == NULL) memory->head = current_allocation->next;
                else previous_allocation->next = current_allocation->next;
                
            free(current_allocation);
            break;
        }
        previous_allocation = current_allocation;
        current_allocation = current_allocation->next;
    }
}

void mymemory_release(mymemory_t *memory) {
    if (memory == NULL) return;

    allocation_t *next_allocation;
    allocation_t *current_allocation = memory->head;
    while (current_allocation != NULL) {
        next_allocation = current_allocation->next;
        mymemory_free(memory, current_allocation);
        current_allocation = next_allocation;
    }
    free(memory->pool);
    free(memory);
}

void mymemory_display(mymemory_t *memory) {
    allocation_t *current_allocation = memory->head;
    while (current_allocation != NULL) {
        printf("\nstart=%p\n", current_allocation->start);
        printf("size=%zu\n", current_allocation->size);
        current_allocation = current_allocation->next;
    }
}

void mymemory_stats(mymemory_t *memory) {
    allocation_t *current_allocation = memory->head;

    int count_allocations = 0;
    size_t allocated_memory = 0;
    size_t largest_free_block = 0;
    int free_memory_fragments = 0;
    
    while (current_allocation != NULL) {
        count_allocations++;
        allocated_memory += current_allocation->size;
        current_allocation = current_allocation->next;
    }
    
    size_t free_memory = memory->total_size - allocated_memory;

    current_allocation = memory->head;
    while (current_allocation != NULL) {
        if (current_allocation->next == NULL) break;
        if ((size_t) (current_allocation->next->start - (current_allocation->start + current_allocation->size)) > 0) free_memory_fragments++;
        current_allocation = current_allocation->next;
    }

    if (memory->head == NULL) largest_free_block = memory->total_size;
        else largest_free_block = memory->total_size - (size_t) (current_allocation->start + current_allocation->size - memory->pool);

    size_t current_free_block = (size_t) (memory->head->start - memory->pool);
    if (current_free_block > largest_free_block) largest_free_block = current_free_block;

    current_allocation = memory->head;
    while (current_allocation != NULL) {
        if (current_allocation->next == NULL) break;
        current_free_block = (size_t) (current_allocation->next->start - (current_allocation->start + current_allocation->size));
        if ((current_free_block > largest_free_block)) largest_free_block = current_free_block;
        current_allocation = current_allocation->next;
    }

    printf("Número total de alocações: %d\n", count_allocations);
    printf("Memória total alocada: %zu\n", allocated_memory); 
    printf("Memória total livre: %zu\n", free_memory);
    printf("Maior bloco contíguo de memória livre: %zu\n", largest_free_block);
    printf("Número de fragmentos de memória livre: %d\n", free_memory_fragments);
}