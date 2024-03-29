/*
 * (C) Michel Megens, 2012
 */

/** \file */

#include <stdlib.h>
#include <error.h>

#ifdef WINDOWS
#include <types.h>
#endif

#ifndef __LIST_H
#define __LIST_H

struct xornode;

typedef hook_result_t (*xor_list_iterator_t)(struct xornode*);

/**
 * \typedef NODE
 * \brief The linked list nodes the library works with.
 */
typedef struct xornode
{
        /**
         * \var pointer
         * \brief In the pointer variable are the previous and next pointer stored.
         * \var value
         * \brief Debug value.
         */
        void *pointer;
        unsigned int value;
} NODE;

/**
 * \fn xorll_get_next(NODE *prev, NODE *this)
 * \return The next node
 * \brief Calculates the next node.
 *
 * Uses the XOR functionality to calculate the next node from the previous and
 * the next pointer.
 */
NODE *xorll_get_next(NODE *prev, NODE *this);

/**
 * \fn xorll_list_insert(NODE *prev, NODE *this, NODE *new)
 * 
 * \param prev Previous pointer of <i>this</i>.
 * \param this The node will be after <i>this</i>
 * \param new The list node to add to the list.
 * \brief Adds <b>new</b> to the list.
 * 
 * \return The error code.
 * \warning <i>prev</i> and <i>this</i> MUST be consecutive.
 *
 * This function will insert the xornode node after the <i>this</i> node.
 */
int xorll_list_insert(NODE *prev, NODE *this, NODE *new);

/**
 * \fn xorll_remove_node(NODE *prev, NODE *this)
 * \param prev Previous node of <i>this</i>
 * \param this Node which has to be removed.
 * \brief Remove node <i>this</i> from the list.
 * 
 * xorll_remove_node removes node <i>this</i> from the linked list.
 */
int xorll_remove_node(NODE *prev, NODE *this);

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
int xorll_list_add(NODE *listHead, NODE *node, NODE *new);

/**
 * \fn iterate_xor_list(NODE *prev, NODE *head, xor_list_iterator_t hook)
 * \param prev Previous node of the starting point <i>head</i>
 * \param head Iterate starting point.
 * \param hook Will be called every iteration.
 * \return An error code.
 * \brief Iterates trough a XOR linked list.
 *
 * This function returns trough a XOR-linkedlist and it will call hook on every
 * iteration.
 */
int iterate_xor_list(NODE *prev, NODE *head, xor_list_iterator_t hook);

/**
 * \fn get_prev_node(NODE *this, NODE *next)
 * \param this 'Current' node.
 * \param next Consecutive node of <i>this</i>.
 * \brief This function returns the previous node of <i>this</i>
 * \return The previous node of <i>this</i>.
 *
 * This function calculates the previous node of <i>this</i> using the <i>next</i>
 * node.
 */
static inline NODE*
get_prev_node(NODE *this, NODE *next)
{
        return (NODE*)((this) ? (ulong)this->pointer ^ (ulong)next : 0);
}

#endif
