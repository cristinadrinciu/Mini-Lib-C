// SPDX-License-Identifier: BSD-3-Clause

#include <internal/mm/mem_list.h>
#include <internal/types.h>
#include <internal/essentials.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

void *malloc(size_t size)
{
    // find a place for malloc with mmap
    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }

    if (mem_list_add(mem, size) == -1) {
        // if the found area does not have enough size, delete what has been chained
        munmap(mem, size);
        return NULL;
    }

    return mem;
}

void *calloc(size_t nmemb, size_t size)
{
	// same as malloc, but all memory is set to 0
	// find a place for malloc with mmap
    void *mem = mmap(NULL, size, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS, -1, 0);
    if (mem == MAP_FAILED) {
        return NULL;
    }

    if (mem_list_add(mem, size) == -1) {
        // if the found area does not have enough size, delete what has been chained
        munmap(mem, size);
        return NULL;
    }

    // set the area with 0

    memset(mem, 0 , size);

    return mem;
}

void free(void *ptr) {
    if (ptr == NULL) {
        return; // No memory area to free
    }

    struct mem_list *item = mem_list_find(ptr);

    if (item != NULL) {
		munmap(item->start, item->len);
        // Remove the item from the memory list.
        mem_list_del(item->start);


        // Unmap the memory block.
        }
}

void *realloc(void *ptr, size_t size)
{
    struct mem_list *area = mem_list_find(ptr);

    if (area != NULL) {
        size_t total_size = size + sizeof(struct mem_list);

        if (total_size <= area->len + sizeof(struct mem_list)) {
            return ptr;
        } else {
            void *new_ptr = malloc(size);
            if (new_ptr != NULL) {
                memcpy(new_ptr, ptr, area->len);
                free(ptr);
            }
            return new_ptr;
        }
    }

    return NULL;
}

void *reallocarray(void *ptr, size_t nmemb, size_t size)
{
	if (nmemb == 0 || size == 0) {
        free(ptr);
        return NULL;
    }
    
    size_t total_size = nmemb * size;
    void *new_ptr = malloc(total_size);
    if (new_ptr != NULL) {
        if (ptr != NULL) {
            struct mem_list *area = mem_list_find(ptr);
            if (area != NULL) {
                size_t copy_size = (area->len < total_size) ? area->len : total_size;
                memcpy(new_ptr, ptr, copy_size);
            }
            free(ptr);
        }
    }

    return new_ptr;
}

