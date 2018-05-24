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
	node_t *node = init_node(NULL, NONE);

	cr_expect(node->buffer == NULL);
	cr_expect_eq(node->quote, NONE);
	cr_expect_eq(node->separator, 0);
	cr_expect_eq(node->fg, false);
	cr_expect_eq(node->backslash, false);
	cr_expect(node->next == NULL);
	node = init_node("Hello World", SIMPLE);
	cr_expect_str_eq(node->buffer, "Hello World");
	cr_expect_eq(node->quote, SIMPLE);
	cr_expect_eq(node->separator, 0);
	cr_expect_eq(node->fg, false);
	cr_expect_eq(node->backslash, false);
	cr_expect(node->next == NULL);
	free(node->buffer);
	free(node);
}