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
		free(*current_path);
		*current_path = strdup("/");
		return (1);
	}
	if ((*arg)[pos] != '/')
		return (1);
	if ((*arg)[pos + 1] != '\0' && (*arg)[pos - 1] != '/')
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

int misspell_process(char **arg, int *pos, char *current_path, int check)
{
	char *cp_path[2] = {prepare_copy(arg, current_path), current_path};
	glob_t pg;
	char *path_star = concat(cp_path[1], "*", 0, 0);
	int size_check[2] = {0, check};

	if ((check = before_correct(cp_path[0], arg, &pg, path_star)))
		return (free_ret_nb(&path_star, &(cp_path[0]), NULL, check));
	if (((size_check[0] = strlen(cp_path[0])) || 1) && size_check[0] >= 4)
		if ((check = correct_long(&(cp_path[0]), &pg, cp_path[1]))) {
			return ((check != 42) ? free_ret_nb(&path_star, \
&(cp_path[0]), &pg, 2) : free_ret_nb(&path_star, &(cp_path[0]), &pg, 42));
		} else
			check = success_case(pos, cp_path, size_check, arg);
	else
		if ((check = correct_short(&(cp_path[0]), &pg, cp_path[1]))) {
			return ((check != 42) ? free_ret_nb(&path_star, \
&(cp_path[0]), &pg, 2) : free_ret_nb(&path_star, &(cp_path[0]), &pg, 42));
		} else
			check = success_case(pos, cp_path, size_check, arg);
	return (free_ret_nb(&path_star, &(cp_path[0]), \
&pg, ((check == 0) ? 0 : 1)));
}

char *check_path_argv(int *nb_to_path, char **arg, jarg_t *corr)
{
	char *current_path = strdup("./");
	int to_know = is_slash_ending(arg);
	int let = remove_mutliple_ending_slash(arg);

	for (int pos = 0; (*arg)[pos] != '\0'; pos++) {
		if (put_back_ending_slash(pos, arg, to_know))
			break;
		if (pre_process_check(&let, arg, pos, &current_path))
			continue;
		if (let == 0 && access(*arg, F_OK) == -1 && ((*arg)[pos] = '/'))
			return (free_return_pointer(&current_path, NULL));
		else if (let != 0 && \
(let = misspell_process(arg, &pos, current_path, 0)) > 0)
			return ((let != 42) ? \
free_return_pointer(&current_path, NULL) : current_path);
		*nb_to_path = pos + 1;
		corr->change = (let == 0) ? 1 : corr->change;
		if (post_misspell_process(&let, arg, &current_path, pos))
			return (free_return_pointer(&current_path, NULL));
	}
	return (current_path);
}

int misspell_handle(jarg_t *corr, comm_t *comm)
{
	char *path = NULL;
	int nb_to_path = 0;
	int check = 0;

	for (int i = 0; corr->infos[i].pos != -1; i++) {
		if (check == 1)
			free(path);
		check = 0;
		if (corr->infos[i].correct == 0) {
			path = \
check_path_argv(&nb_to_path, &(comm->argv[i + 1]), corr);
			path = \
final_check_path(path, nb_to_path, &(comm->argv[i + 1]), corr);
			check = 1;
		}
		if (check == 1 && path == NULL)
			return (free_ret_nb(&path, NULL, NULL, -1));
	}
	if (check == 1)
		free(path);
	return (0);
}