/*
 * (C) Michel Megens, 2012
 */

/** \file */

#ifndef __LIST_H
#define __LIST_H

#include <stdlib.h>

typedef struct xornode
{
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
 * \fn xorll_list_insert(NODE *alpha, NODE *beta, NODE *node)
 * \brief Adds <b>node</b> to <b>list</b>.
 * \param alpa The node will be inserted after alpha.
 * \param beta The node will be inserted before beta.
 * \param node The list node to add to the list.
 * \warning <i>alpha</i> and <i>beta</i> MUST be linked to together directly!
 *
 * This function will insert the xornode node between alpha and beta.
 */
static int xorll_list_insert(NODE *alpa, NODE *beta, NODE *node);

#endif
