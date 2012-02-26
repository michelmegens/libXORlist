/*
 * (C) Michel Megens, 2012
 */

/** \file */

#include <stdlib.h>
#include <stdio.h>

#ifdef WINDOWS
#include <types.h>
#endif

#include <list.h>
#include <error.h>

static inline void print_node(int it, NODE *node)
{
        printf("Iterator: %i, Node value: 0x%X\n", it, node->value);
}

/**
 * \fn xorll_get_next(NODE *prev, NODE *this)
 * \return The next node
 * \brief Calculates the next node.
 *
 * Uses the XOR functionality to calculate the next node from the previous and
 * the next pointer.
 */
NODE *
xorll_get_next(NODE *prev, NODE *this)
{
        if(this == NULL)
                return this;
        ulong uprev = (ulong)prev;
        ulong uthis = (ulong)((this) ? this->pointer : NULL);

        ulong next = uprev ^ uthis;

        return (NODE*)next;
}

/**
 * \fn xorll_list_insert(NODE *prev, NODE *this, NODE *new)
 * \brief Adds <b>node</b> to <b>list</b>.
 * \param prev The previous node
 * \param this The node will be after this node.
 * \param new The list node to add to the list.
 * \warning <i>prev</i> and <i>this</i> MUST be consecutive nodes.
 *
 * This function will insert the xornode node between alpha and beta.
 */
int
xorll_list_insert(NODE *prev, NODE *this, NODE *new)
{
        ulong uprev = (ulong)prev;
        ulong uthis = (ulong)this;
        ulong unew  = (ulong)new;
        NODE *next  = xorll_get_next(prev, this);
        ulong unext = (ulong)next;

        ulong pNext_next = (next) ? (ulong)next->pointer ^ uthis : 0 ^ uthis;
        
        if(NULL == next)
        {
                this->pointer = (void*)(uprev ^ unew);
                new->pointer = (NODE*)(uthis ^ 0);
                return OK;
        }

        /* set the node pointer of this */
        this->pointer = (NODE*)(uprev ^ unew);
        new->pointer = (NODE*)(uthis ^ unext);
        next->pointer = (NODE*)(pNext_next ? unew ^ pNext_next : unew ^ 0);
        return OK;
}

/**
 * \fn xorll_remove_node(NODE *prev, NODE *this)
 * \param prev Previous node of <i>this</i>
 * \param this Node which has to be removed.
 * \brief Remove node <i>this</i> from the list.
 * 
 * xorll_remove_node removes node <i>this</i> from the linked list.
 */
int
xorll_remove_node(NODE *prev, NODE *this)
{
        if(NULL == this)
                return NULL_PTR;
        
        NODE *next = xorll_get_next(prev, this);
        ulong uprev_prev = (ulong) ((prev) ? get_prev_node(prev, this) : NULL);
        
        ulong unext = (ulong)next;
        ulong uprev = (ulong)prev;
        ulong uthis = (ulong)this;
        ulong unext_next = (ulong) ((next) ? (ulong)next->pointer ^ uthis : 0);
        
        if(NULL != prev)
                prev->pointer = (void*)(uprev_prev ^ unext);
        
        if(NULL != next)
                next->pointer = (void*)(unext_next ^ uprev);
        this->pointer = NULL;
//         printf("%x\n", next->pointer);
        return OK;
}

/**
 * \fn xorll_list_add(NODE *list, NODE *node, NODE *new)
 * \brief Add the node <i>new</i> to <i>list</i>.
 * \param list The list head.
 * \param node The node to add the new node after.
 * \param new The node to add after <i>node</i>.
 * \return ERROR code.
 *
 * The xornode <i>new</i> will be added after <i>node</i> in the list
 * <i>list</i>.
 */
int
xorll_list_add(NODE *listHead, NODE *node, NODE *new)
{
        NODE *prev = NULL,*carriage = listHead, *tmp;

        if(!new)
                return NULL_PTR;
        while(carriage)
        {
                if(carriage == node)
                {
                        xorll_list_insert(prev, carriage, new);
                        break;
                }
                tmp = carriage;
                carriage = xorll_get_next(prev, tmp);                
                prev = tmp;
                
                if(!carriage && !node && new)
                {
                        carriage = tmp;
                        prev = get_prev_node(carriage, NULL);
                        xorll_list_insert(prev, carriage, new);
                        break;
                }
        }
        
        return OK;
}

int
iterate_xor_list(NODE *prev, NODE *head, xor_list_iterator_t hook)
{
        NODE *carriage = head, *tmp;
        int result = -1;

        if(!hook)
                return NULL_PTR;
        while(carriage)
        {
                tmp = carriage; // save to set prev later
                carriage = xorll_get_next(prev, tmp); // get next one..
                if(prev)
                        if(HOOK_DONE == (result = hook(prev)))
                                break;
                prev = tmp;
        }
        result = hook(prev);

        return result;
}
