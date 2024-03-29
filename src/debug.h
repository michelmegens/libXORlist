/**
  * \author Michel Megens
  * \copyright 2012
  */
  
#ifndef __DEBUG_H
#define __DEBUG_H
#ifdef WINDOWS
#include <types.h>
#endif
static int init_list();
static int init(unsigned int num);
static void print_list();

static void print_node(int it, NODE *node);

static void destroy_list();

// #pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wformat"
static inline void print_node(int it, NODE *node)
{
        if(NULL == node)
        {

                printf("Node %i equals NULL.\n", node);
                return;
        }
        printf("Iterator: %i, Node value: 0x%X, Node pointer: %X\n", it, 
                        node->value, (ulong)node);

}
// #pragma GCC diagnostic pop
#endif
