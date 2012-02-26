/*
 * (C) Michel Megens, 2012
 */

#include <stdlib.h>
#include <stdio.h>
#include <list.h>
#include <string.h>

#ifdef WINDOWS
#include <types.h>
#endif

#include "debug.h"
#include <error.h>

static NODE *pHead = NULL;

int main(void)
{
        init(5);
        getchar();
        print_list();
        getchar();
        destroy_list();
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

static int
init(unsigned int num)
{
        pHead = malloc(sizeof(*pHead));
        if(NULL == pHead)
                return NO_MEM;

        pHead->value = 0x100;
        pHead->pointer = NULL;
        
        NODE *new = NULL;

        printf("Adding nodes:\n");
        int i = 0;
        for(; i < num; i++)
        {
                new = calloc(1, sizeof(*new));
                new->value = i;
                xorll_list_add(pHead, NULL, new);
                print_node(i, new);
        }
        putc('\n', stdout);
        return OK;
}


static void
print_list()
{
        auto hook_result_t it_print_node(NODE *node);

        iterate_xor_list(NULL, pHead, &it_print_node);

        auto hook_result_t it_print_node(NODE *node)
        {
                print_node(0, node);
                return HOOK_NOT_DONE;
        }
}

static void
destroy_list()
{
        auto hook_result_t free_node(NODE *this);

        iterate_xor_list(NULL, pHead, &free_node);
        return;

        auto hook_result_t
        free_node(NODE *this)
        {
                memset(this, 0, sizeof(*this));
                free(this);
                return HOOK_NOT_DONE;
        }
}
