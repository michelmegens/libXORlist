/*
 * (C) Michel Megens, 2012
 */

/** \file */

#include <stdlib.h>
#include <stdio.h>
#include "list.h"
#include "error.h"

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
        ulong uprev = (ulong)prev;
        ulong uthis = (ulong)this->pointer;

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
        if(NULL == next)
        {
                this->pointer = new;
                return OK;
        }

        /* set the node pointer of this */
        this->pointer = (NODE*)(uprev ^ unew);
        new->pointer = (NODE*)(uthis ^ unext);
        ulong pNext_next = (unew ^ ((ulong)next->pointer));
        next->pointer = (NODE*)(pNext_next ? unew ^ pNext_next : unew ^ 0);
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
xorll_list_add(NODE *list, NODE *node, NODE *new)
{
        
}
