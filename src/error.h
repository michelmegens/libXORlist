/**
 * \file error.h
 * \author Michel Megens
 */

#ifndef __ERROR_H
#define __ERROR_H

typedef enum
{
        OK = 0,
        NULL_PTR,
        GENERAL_ERR,
        NO_MEM,
} error_t;

#endif