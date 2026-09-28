// Simulation of a basic memory allocator and garbage collector using doubly linked list.

#include <stdio.h>
#include <stdlib.h>

// Structure for a memory block in the doubly linked list
typedef struct MemoryBlock {
    int size;
    struct MemoryBlock* next;
    struct MemoryBlock* prev;
} MemoryBlock;

// Structure for the memory allocator
typedef struct MemoryAllocator {
    MemoryBlock* head;
} MemoryAllocator;

// Function to create a new memory block
MemoryBlock* createMemoryBlock(int size) {
    MemoryBlock* block = malloc(sizeof(MemoryBlock));
    if (!block) {
        printf("Error: Failed to allocate memory for a new block.\n");
        exit(1);
    }
    block->size = size;
    block->next = NULL;
    block->prev = NULL;
    return block;
}

// Function to initialize the memory allocator
MemoryAllocator* initializeAllocator() {
    MemoryAllocator* allocator = malloc(sizeof(MemoryAllocator));
    if (!allocator) {
