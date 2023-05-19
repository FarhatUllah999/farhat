#include "buddy.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define HALF 2

buddy_allocator_t *
buddy_allocator_create(void *raw_memory, size_t raw_memory_size)
{
    buddy_allocator_t *newBuddy = (buddy_allocator_t *)malloc(sizeof(buddy_allocator_t));
    if(NULL == newBuddy){
        printf("Failed to allocate memory\n");
        return NULL;
    }

    memset(newBuddy, 0x0, sizeof(buddy_allocator_t));

    /* allocate memory of the given size */
    raw_memory = malloc(raw_memory_size);
    if(NULL == raw_memory){
        free(newBuddy);
        printf("Failed to allocate memory\n");
        return NULL;
    }

    /* create and populate the first node of double linked-list */
    node_t *new = malloc(sizeof(node_t));
    memset(new, 0x0, sizeof(node_t));

    new->memsize  = raw_memory_size;
    new->memptr   = raw_memory;
    new->isbusy   = false;
    new->next     = NULL;
    new->previous = NULL;

    memset(raw_memory, 0, raw_memory_size);

    newBuddy->memsize    = raw_memory_size;
    newBuddy->raw_memory = raw_memory;
    newBuddy->liststart  = new;
    newBuddy->listend    = new;

    return newBuddy;
}

void *
buddy_allocator_alloc(buddy_allocator_t *buddy_allocator, size_t size)
{
    static unsigned int id = 1;
    node_t *ptr = buddy_allocator->listend;

    /* find the first free block by traversing the doubly linked-list */
    while ((ptr->isbusy) && (ptr != buddy_allocator->liststart)){
        ptr = ptr->previous;
    }

    /* find the first free block by traversing the doubly linked-list */
    while ((size > ptr->memsize) && (ptr != buddy_allocator->liststart)){
        ptr = ptr->previous;
    }

    /* check if the memory is full */
    if ((ptr == buddy_allocator->liststart) && ((ptr->isbusy) || (size > ptr->memsize))){
        printf("memory is full\n");
        return NULL;
    }

    /* divide the memory block by 2 if the block is 2x or more greater than the requested size */
    while (size <= (ptr->memsize - size) && (!(ptr->isbusy))){
        ptr->memsize = ptr->memsize/HALF;

        /* allocate buddy node */
        node_t *new = malloc(sizeof(node_t));
        memset(new, 0x0, sizeof(node_t));

        new->memsize = ptr->memsize;
        new->memptr = ptr->memptr + new->memsize;
        new->isbusy = false;
        new->next = ptr->next;
        new->previous = ptr;

        ptr->id = new->id = id++;
        ptr->next = new;
        ptr = new;
    }

    buddy_allocator->listend = ptr;
    ptr->isbusy = true;

    /* return pointer to the memory allocated for the requested size */
    return ptr->memptr;
}

void
buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr)
{
    if (ptr == NULL)
        return;

    node_t *node = buddy_allocator->listend;

    /* find the memory block */
    while (node->memptr != ptr){
        node = node->previous;
    }

    /* free the memory block */
    if (node->memptr == ptr){
        node_t *next = node->next;
        node_t *prev = node->previous;

        memset(node->memptr, 0x0, node->memsize);
        node->isbusy = false;

        /* merge the memory block with the previous node if previous is free and have the same buddy id */
        if ((prev->isbusy == false) && (prev->memsize == node->memsize) && (prev->id == node->id)){
            prev->memsize += node->memsize;
            prev->next = next;

            if ((next != NULL) && (next->previous != NULL))
                next->previous = prev;

            if(node->next == NULL)
                buddy_allocator->listend = prev;

            if (node != buddy_allocator->liststart)
                free(node);

            return;
        }

        /* merge the memory block with the next node if next is free and have the same buddy id */
        if ((next->isbusy == false) && (next->memsize == node->memsize) && (next->id == node->id)){
            node_t *ptr = next->next;

            node->memsize += next->memsize;
            node->next = next->next;

            if(next->next == NULL)
                buddy_allocator->listend = node;

            if (ptr != NULL)
                ptr->previous = node;

            if (next != buddy_allocator->liststart)
                free(next);

            return;
        }
    }

    return;
}

void
buddy_allocator_destroy(buddy_allocator_t *buddy_allocator)
{
    node_t *ptr, *node = buddy_allocator->listend;

    /* free all the nodes in the doubly linked-list */
    while(node != buddy_allocator->liststart){
        ptr = node;
        node = node->previous;

        free(ptr);
    }

    free(buddy_allocator->raw_memory);

    if(buddy_allocator->liststart)
        free(buddy_allocator->liststart);

    free(buddy_allocator);

    return;
}

int main()
{
    void *raw_mem;

    /* create a memory pool of 1000 bytes */
    buddy_allocator_t *buddy = buddy_allocator_create(raw_mem, 1000);

    /* allocate memory of 200 bytes */
    void *ptr0 = buddy_allocator_alloc(buddy, 200);

    /* allocate memory of 200 bytes */
    void *ptr1 = buddy_allocator_alloc(buddy, 200);

    /* allocate memory of 200 bytes */
    void *ptr2 = buddy_allocator_alloc(buddy, 200);

    /* free first memory block */
    buddy_allocator_free(buddy, ptr0);

    /* free second memory block */
    buddy_allocator_free(buddy, ptr1);

    /* free third memory block */
    buddy_allocator_free(buddy, ptr2);

    /* free the memory pool */
    buddy_allocator_destroy (buddy);

    return 0;
}

