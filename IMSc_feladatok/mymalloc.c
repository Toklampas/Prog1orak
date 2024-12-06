#include <stdio.h>
#include <stddef.h>
#include <string.h>

#define MEMORY_SIZE 500  // Adjusted size for testing

typedef struct Block {
    struct Block* next;
    size_t size;
} Block;

void* free_blocks;

void* own_malloc(size_t size)
{
    Block* current = (Block*)free_blocks;
    Block* previous = NULL;

    while (current)
    {
        if (current->size >= size)
        {
            if (current->size > size + sizeof(Block))
            {
                size_t new_size = current->size - size - sizeof(Block);
                Block* alloc_block = (Block*)((char*)current + sizeof(Block) + new_size);
                alloc_block->size = size;

                current->size = new_size;

                return (char*)alloc_block + sizeof(Block);
            }
            else
            {
                if (previous)
                    previous->next = current->next;
                else
                    free_blocks = current->next;

                current->next = NULL;

                return (char*)current + sizeof(Block);
            }
        }
        previous = current;
        current = current->next;
    }

    return NULL;
}

void own_free(void* ptr)
{
    if (!ptr) return;

    Block* block = (Block*)((char*)ptr - sizeof(Block));

    Block* current = (Block*)free_blocks;
    Block* previous = NULL;

    while (current && current < block)
    {
        previous = current;
        current = current->next;
    }

    block->next = current;
    if (previous)
        previous->next = block;
    else 
        free_blocks = block;

    if (previous && ((char*)previous + sizeof(Block) + previous->size == (char*)block))
    {
        previous->size += sizeof(Block) + block->size;
        previous->next = block->next;
        block = previous;
    }

    if (current && ((char*)block + sizeof(Block) + block->size == (char*)current))
    {
        block->size += sizeof(Block) + current->size;
        block->next = current->next;
    }
}

char memory_arena[MEMORY_SIZE];

void reset_memory_arena() {
    memset(memory_arena, 0, MEMORY_SIZE);
    free_blocks = NULL;
}

// Function to initialize free blocks manually
void initialize_free_blocks(Block* blocks[], size_t sizes[], int count) {
    reset_memory_arena();
    size_t offset = 0;
    for (int i = 0; i < count; i++) {
        blocks[i] = (Block*)(memory_arena + offset);
        blocks[i]->size = sizes[i];
        blocks[i]->next = NULL;
        offset += sizeof(Block) + sizes[i];
        if (i > 0) {
            blocks[i - 1]->next = blocks[i];
        }
    }
    free_blocks = blocks[0];
}

void print_free_blocks() {
    Block* current = (Block*)free_blocks;
    printf("Free blocks:\n");
    while (current) {
        printf("  Block at %td, size = %zu bytes\n", (ptrdiff_t)((char*)current - memory_arena), current->size);
        current = current->next;
    }
}

int main(void) {
    printf("Test Case #6: One free block (100 bytes excluding header), calling own_malloc(100 - HEADER_SIZE)\n");
    {
        Block* blocks[1];
        size_t sizes[1] = {100};
        initialize_free_blocks(blocks, sizes, 1);

        size_t alloc_size = 100 - sizeof(Block);
        void* ptr = own_malloc(alloc_size);
        printf("Allocated %zu bytes at offset %td\n", alloc_size, (ptrdiff_t)((char*)ptr - memory_arena));

        printf("After allocation:\n");
        print_free_blocks();

        // Expected: free_blocks is NULL
        if (free_blocks == NULL)
            printf("free_blocks is NULL as expected.\n");
        else
            printf("free_blocks is not NULL, which is incorrect.\n");
    }
    return 0;
}