#include <stddef.h>

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