/*
** EPITECH PROJECT, 2017
** parsing.c
** File description:
** Parsing fnc
*/

#include <stdlib.h>
#include <unistd.h>
#include "minishell.h"
#include "my.h"
#include "tokens.h"

int is_tk(char *input)
{
	if (input[0] == '\0')
		return (-1);
	for (int i = 0; tokens[i].tk; i++)
		if (!my_strcmp(tokens[i].tk, input, my_strlen(tokens[i].tk)))
			return (i);
	return (-1);
}

char *go_next_w(char *input, const char *separator)
{
	while (index_of(separator, input[0]) != -1)
		input++;
	return (input);
}

int parse_command(char *input, comm_t *comm)
{
	int tk;
	int len;

	while (input && input[0]) {
		input = go_next_w(input, separators);
		tk = is_tk(input);
		if (tk != -1) {
			if ((comm->red[tk] = init_redir()) == NULL)
				return (-1);
			input = tokens[tk].fnc(input, comm);
		} else {
			len = adv_get_wlen(input, separators, ign_delim, \
ign_delim);
			if ((comm->argv = add_arr(comm->argv, my_strndup\
(input, len), 1)) == NULL)
				return (-1);
			input += len;
		}
	}
	if (input[0])
		return (-1);
	return (0);
}

comm_t **full_parse(char *input)
{
	char **first = adv_parse(input, ";", ign_delim, ign_delim);
	int len = array_len((void **) first);
	comm_t **res = malloc(sizeof(comm_t *) * (len));

	if ((res == NULL) || (first == NULL))
		return (NULL);
	for (int i = 0; first[i] != NULL; i++) {
		if ((res[i] = init_comm()) == NULL)
			return (NULL);
		if (parse_command(first[i], res[i]) == -1)
			return (NULL);
	}
	res[len - 1] = NULL;
	free_array((void **) first);
	return (res);
}