/*
** EPITECH PROJECT, 2017
** 42sh
** File description:
** 42sh
*/

#include "my.h"
#include "parsing.h"
#include <stdio.h>

int main(void)
{
	char *buffer = \
"(Hello) ;; World, \"this is ;a sim(pl)e ' test\" 'for parsing\\', \
'`is it working ?` lol";
	node_t *node = init_node(buffer, NONE);

	if (node == NULL)
		return (84);
	node = parse_quote(node, buffer);
	if (node == NULL)
		return (84);
	printf("%s\n", node->buffer);
	for (int i = 0; node->next[i] != NULL; i++)
		for (int j = 0; node->next[i]->next[j] != NULL; j++)
//			for (int k = 0; node->next[i]->next[j]->next[k] != NULL; k++)
				printf("|\n|\n-->%s\n", node->next[i]->next[j]->buffer);
	free_node(node);
	return (0);
}