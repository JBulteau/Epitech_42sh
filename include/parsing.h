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
#include <glob.h>

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
	D_AMPERSAND,
	D_PIPE,
	S_AMPERSAND,
	S_PIPE,
	S_ARROW_LEFT,
	D_ARROW_LEFT,
	S_ARROW_RIGHT,
	D_ARROW_RIGHT
};

typedef struct node node_t;

struct node {
	char *buffer;
	quote_type_t quote;
	separator_type_t separator;
	bool fg;
	bool backslash;
	node_t **next;
};

#define REDIR(value) (value >= S_ARROW_LEFT && value <= D_ARROW_RIGHT)

/* parsing.c */

comm_t **parsing(char *buffer);

/* init_comm_array.c */

comm_t **init_comm_array(comm_t **comm, node_t *node);
int get_nb_comm(node_t *node);

/* convert_node.c */

comm_t **convert_node(comm_t **comm, node_t *node);
comm_t *fill_comm(comm_t *comm, node_t *node, int *node_index);
void check_node(node_t *node, int index[3]);
comm_t *convert_param(comm_t *comm, node_t *node, int *comm_index);
char **parse_argv(char **argv, node_t *node, int *comm_index, int index);

/* handle_separators.c */

comm_t *handle_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index);
comm_t *handle_advanced_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index);
comm_t *handle_basic_separators(comm_t *comm, node_t *node, int idx[3], \
int *comm_index);
comm_t *apply_separator(comm_t *comm, node_t *node[2], int *comm_index, \
separator_type_t separator);
comm_t *set_separator(comm_t *comm, node_t *node[2], \
separator_type_t separator, int *new_index);

/* struct.c */

node_t *init_node(char *buffer, quote_type_t quote);
node_t **realloc_node(node_t **node, int n, quote_type_t quote);
node_t *copy_node(node_t *dest, node_t *src);

/* quote.c */

node_t *parse_quote(node_t *node, char *buffer);
node_t *delete_quote(node_t *node, char *buffer, int i);
node_t *new_quoted_node(node_t *node, int index[], char *buffer, int i);
node_t *no_quote(node_t *node, char *buffer, int i, int *j);
int missing_quote(node_t *node, char *buffer);

/* is_quote.c */

int is_a_quote(char c);
int is_simple(char c);
int is_double(char c);
int is_magic(char c);

/* split.c */

node_t *parse_split(node_t *node);
node_t *search_separators(node_t *node);
node_t *parse_separators(node_t *node, char *buffer, int *i);
separator_type_t is_separator(char *buffer, int *i);

/* parentheses.c */

node_t *parse_parentheses(node_t *node);
node_t *check_parentheses(node_t *node, char *buffer);

/* globbing.c */

node_t *parse_globbing(node_t *node);
node_t *check_globbing(node_t *node);
node_t *isolate_glob(node_t *node, int i);
node_t *replace_glob(node_t *node, glob_t pglob, int j, size_t len);

/* cmd_separators.c */

node_t *parse_cmd_separators(node_t *node);
node_t *fill_cmd_separators(node_t *node, char *buffer, int *i);
node_t *attribute_cmd_separator(node_t *node, int index[], int *i, char *buffer);
separator_type_t check_cmd_separator(char *buffer, int *i, node_t *node);
separator_type_t check_arrow(char *buffer, int *i, \
separator_type_t arrow);

/* browse_node.c */

node_t *browse_sep_node(node_t *node);
node_t *browse_glob_node(node_t *node);
node_t *search_cmd_separators(node_t *node);
node_t *fill_buffer(node_t *node, char *buffer, int *i);

/* is_cmd_separator.c */

int is_cmd_separator(char c);
int is_pipe(char c);
int is_l_arrow(char c);
int is_r_arrow(char c);
int is_ampersand(char c);

/* free_node.c */

void free_node(node_t *node);

#endif
