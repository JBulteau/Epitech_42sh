/*
** EPITECH PROJECT, 2017
** Unit Tests
** File description:
** Unit tests for struct functions
*/

#include "my.h"
#include "parsing.h"
#include <criterion/criterion.h>
#include <string.h>

Test(struct, init_node)
{
	cr_expect_eq(memcmp(init_node(NULL, 0), &((node_t){NULL, 0, NULL}), \
sizeof(node_t)), 0);
}