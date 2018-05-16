/*
** EPITECH PROJECT, 2017
** jarvis_corrector_process.c
** File description:
** function to process our corrector
*/

#include "jarvis.h"
#include <sys/types.h>
#include <dirent.h>
#include <glob.h>
#include <unistd.h>
#include <string.h>

int pre_process_check(int *letter_nbr, char **arg, int pos, char **current_path)
{
	(*letter_nbr) += (is_number_or_letter(arg, pos)) ? 1 : 0;
	if ((pos == 0 && (*arg)[pos] == '/')) {
		*current_path += 1;
		return (1);
	}
	if ((*arg)[pos] != '/' && (*arg)[pos + 1] != '\0')
		return (1);
	if ((*arg)[pos + 1] != '\0')
		(*arg)[pos] = '\0';
	return (0);
}

int post_misspell_process(int *let, char **arg, char **current_path, int pos)
{
	*let = 0;
	(*arg)[pos] = '/';
	free(*current_path);
	*current_path = malloc(sizeof(char) * (pos + 2));
	if (!(*current_path))
		return (1);
	(*current_path)[pos + 1] = '\0';
	for (int i = 0; i <= pos; i++)
		(*current_path)[i] = (*arg)[i];
	return (0);
}

int misspell_process(char **arg, int pos, char *current_path, int *nb_to_path)
{
	char *cpy = prepare_copy(arg, current_path);
	glob_t pglob;
	char *concat_path_star = concat(current_path, "*", 0, 0);

	if (!cpy)
		return (1);
	*nb_to_path = pos + 1;
	if (access(*arg, F_OK) != -1)
		return (0);
	if (glob(concat_path_star, GLOB_NOSORT, NULL, &pglob) != 0)
		return (2);
	if (my_strlen(cpy) >= 4) {
		if (correct_long(&cpy, &pglob))
			return (2);
		else
			printf("test : %s\n", cpy); //refill_arg();
	} else
		if (correct_short(&cpy, &pglob))
			return (2);
		else
			//refill_arg();
	return (0);
}

char *check_path_argv(int *nb_to_path, char **arg, jarg_t *corr, int *check)
{
	char *current_path = strdup("./");
	int to_know = is_slash_ending(arg);
	int let = 0;

	for (int pos = 0; (*arg)[pos] != '\0'; pos++) {
		if (pre_process_check(&let, arg, pos, &current_path))
			continue;
		if (let == 0 && access(*arg, F_OK) == -1 && ((*arg)[pos] = '/'))
			return (NULL);
		else if (let != 0 && (let = misspell_process(arg, pos, current_path, nb_to_path)))
			return (NULL);
		if (let == 2) {
			*check = 1;
			return (current_path);
		} else
			corr->change = 1;
		if (post_misspell_process(&let, arg, &current_path, pos))
			return (NULL);
		if ((*arg)[pos + 1] == '\0' && to_know == 1) {
			(*arg)[pos + 1] = '/';
			break;
		}
	}
	return (current_path);
}

int misspell_handle(jarg_t *corr, comm_t *comm)
{
	char *path = NULL;
	int nb_to_path = 0;
	int check = 0;

	for (int i = 0; corr->infos[i].pos != -1; i++) {
		if (corr->infos[i].correct == 0)
			path = check_path_argv(&nb_to_path, &(corr->infos[i].name), corr, &check);
		if (path == NULL)
			return (-1);
		if (check == 0)
			4;//last_check_path();
	}
	return (0);
}