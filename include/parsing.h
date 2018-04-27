/*
** EPITECH PROJECT, 2018
** 42sh
** File description:
** parsing for 42sh
*/

#ifndef __PARSING_H_
#define __PARSING_H_

#include "minishell.h"

typedef enum quote_type quote_type_t;

enum quote_type {
	NONE = -1,
	SIMPLE,
	DOUBLE,
	MAGIC
};

typedef struct node node_t;

struct node {
	char *buffer;
	quote_type_t quote;
	node_t **next;
};

/*parsing.c*/

comm_t **parsing(char *buffer);

/*struct.c*/

node_t *init_node(char *buffer, int quote);
node_t **realloc_node(node_t **node, int n);

/*quote*/

node_t *parse_quote(node_t *node, char *buffer);
int is_a_quote(char c);
int is_simple(char c);
int is_double(char c);
int is_magic(char c);

#endif
