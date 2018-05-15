/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parsing for 42sh
*/

#ifndef __PARSING_H_
#define __PARSING_H_

#include "minishell.h"
#include <stdbool.h>

typedef enum quote_type quote_type_t;

enum quote_type {
	NONE = -1,
	SIMPLE,
	DOUBLE,
	MAGIC,
	PARENTHESES
};


typedef enum separator_type separator_type_t;

enum separator_type {
	SEMICOLON = 1,
	D_PIPE,
	D_AMPERSAND
};

typedef struct node node_t;

struct node {
	char *buffer;
	quote_type_t quote;
	separator_type_t separator;
	bool backslash;
	node_t **next;
};

/*parsing.c*/

comm_t **parsing(char *buffer);

/*struct.c*/

node_t *init_node(char *buffer, quote_type_t quote);
node_t **realloc_node(node_t **node, int n);

/*quote*/

node_t *parse_quote(node_t *node, char *buffer);
node_t *fill_buffer(node_t *node, char *buffer, int *i);
node_t *delete_quote(node_t *node, char *buffer, int i);
int missing_quote(node_t *node, char *buffer);

/*is_quote.c*/

int is_a_quote(char c);
int is_simple(char c);
int is_double(char c);
int is_magic(char c);

/*split.c*/

node_t *parse_split(node_t *node);
node_t *search_separators(node_t *node);
node_t *parse_separators(node_t *node, char *buffer, int *i);
separator_type_t is_separator(char *buffer, int *i, node_t *node);

/*parentheses.c*/

node_t *parse_parentheses(node_t *node);
node_t *check_parentheses(node_t *node, char *buffer);

/*free_node.c*/

void free_node(node_t *node);

#endif
