/*
 * (C) Michel Megens, 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include "debug.h"
#include "error.h"

static NODE *pHead = NULL;

int main(int argc, char **argv)
{
        init_list();
        return -EXIT_SUCCESS;
}

static int
init_list()
{
        pHead = malloc(sizeof(*pHead));
        if(NULL == pHead)
                return NO_MEM;
        
        pHead->value = 0x100;
        pHead->pointer = NULL;
        print_node(0,pHead);
        
        /*
         * now the head is initialised we can add more nodes.
         */
        NODE *next = calloc(1, sizeof(*next));
        next->value = 0x80;
        xorll_list_insert(NULL, pHead, next);
        print_node(1,xorll_get_next(NULL, pHead));
        return OK;
}

static void
destroy_list()
{
        free(pHead);
}

static inline void
print_node(int it, NODE *node)
{
        printf("Iterator: %i, Node value: 0x%X\n", it, node->value);
}
