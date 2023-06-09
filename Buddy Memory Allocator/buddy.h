
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>

/** @struct node_t
 *  @brief This structure represents a node of doubly linked-list
 *  @var node_t::memsize
 *  Member 'memsize' contains the total size of memory block
 *  @var node_t::memptr
 *  Member 'memptr' contains the starting address to the memory block
 *  @var node_t::isbusy
 *  Member 'isbusy' contains the status of the memory block
 *  @var node_t::id
 *  Member 'id' contains the same id of its buddy block
 *  @var node_t::next
 *  Member 'next' points to the next node
 *  @var node_t::previous
 *  Member 'previous' points to the previous node
 */
typedef struct node
{
    size_t  memsize;
    void   *memptr;
    bool    isbusy;
    uint8_t id;
    struct  node *next;
    struct  node *previous;
} node_t;

/** @struct buddy_allocator_t
 *  @brief This structure contains the memory block
 *  @var buddy_allocator_t::memsize
 *  Member 'memsize' contains the total size of memory block
 *  @var buddy_allocator_t::liststart
 *  Member 'liststart' points to the starting node of the doubly linked-list
 *  @var buddy_allocator_t::listsend
 *  Member 'liststend' points to the last node of the doubly linked-list
 */
typedef struct buddy_allocator_t_
{
    size_t  memsize;
    void   *raw_memory;
    node_t *liststart;
    node_t *listend;
} buddy_allocator_t;


/**
* Create a buddy allocator
* @param raw_memory Backing memory
* @param memory_size Backing memory size
* @return the new buddy allocator
*/
buddy_allocator_t *
buddy_allocator_create(void *raw_memory, size_t raw_memory_size);

/**
* Destroy a buddy allocator
* @param buddy_allocator
*/
void
buddy_allocator_destroy(buddy_allocator_t *buddy_allocator);

/**
* Allocate memory
* @param buddy_allocator The buddy allocator
* @param size Size of memory to allocate
* @return pointer to the newly allocated memory , or @a NULL if out of memory
*/
void *
buddy_allocator_alloc(buddy_allocator_t *buddy_allocator, size_t size);

/**
* Deallocates a perviously allocated memory area.
* If @a ptr is @a NULL , it simply returns
* @param buddy_allocator The buddy allocator
* @param ptr The memory area to deallocate
*/
void
buddy_allocator_free(buddy_allocator_t *buddy_allocator, void *ptr);
