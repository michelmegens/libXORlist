/*
 * (C) Michel Megens, 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <list.h>

#ifdef WINDOWS
#include <types.h>
#endif

#include "debug.h"
#include "error.h"

static NODE *pHead = NULL;

int main(int argc, char **argv)
{
        init_list();
        getchar();
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

        NODE *third = calloc(1, sizeof(*third));
        third->value = 0x40;
        xorll_list_insert(NULL, pHead, third);
        print_node(3, xorll_get_next(NULL, pHead));
        xorll_remove_node(third, next);
        
        xorll_list_add(pHead, third, next);
        print_node(4, xorll_get_next(pHead, third));
        return OK;
}

static void
destroy_list()
{
        free(pHead);
}
