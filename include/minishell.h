/*
** EPITECH PROJECT, 2017
** minishell.h
** File description:
** Header for minishell
*/

#ifndef __MINI__
#define __MINI__

#include <stdlib.h>
#include <linux/limits.h>

typedef struct redir_s redir_t;
typedef struct comm_s comm_t;
typedef struct pipe_s pipe_t;

struct redir_s {
	char *target;
	int fd[2];
};

struct comm_s {
	char **argv;
	redir_t *red[4];
	pipe_t *pipe[2];
};

struct pipe_s {
	int fd[2];
	comm_t *input;
	comm_t *output;
};

typedef struct {
	char **env;
	char pwd[2][PATH_MAX];
	char *input;
	comm_t **comm;
	int return_value;
} shell_t;

/*	shell.c		*/
shell_t *init_shell(char **env);
void delete_shell(shell_t *shell);

/*	parsing.c	*/
int is_tk(char *input);
char *go_next_w(char *input, const char *separator);
char **add_arr(char **arr, char *str, int free_arr);
int parse_command(char *input, comm_t *comm);
comm_t **full_parse(char *input);

/*	commands.c	*/
comm_t *init_comm(void);
void free_comm(comm_t *comm);
void free_comms(comm_t **comm);
int exec_start(comm_t *comm);
int exec_end(comm_t *comm);

/*	display.c	*/
void disp_wrong_arch(char *str, int num);
void display_signal(int status);
void disp_prompt(void);

/*	exec.c		*/
int exec(comm_t *comm, char *path, char **env);
int exec_comm(comm_t *comm, char ***env, char pwd[2][PATH_MAX]);
int exec_loop(shell_t *shell);

/*	search.c	*/
void disp_rights(char *name, int exists, int exec);
int search_local(char *name);
char *search_path(char **path, char *name);
char **get_path(char **env);
char *get_env_var(char **env, char *var);

/*	BUILT-INS	*/
int is_builtin(char *name);
int exec_bi(comm_t *comm, shell_t *shell);

/*	redic.c		*/
redir_t *init_redir(void);
void free_red(redir_t *red);

/*	utils.c		*/
int search_strtab(char **arr, char *to_find);
int check_is_dir(char *fn);

/*	exec.c		*/
int exec_loop(shell_t *shell);
int exec_bin(comm_t *comm, char **env);
int run_bin(comm_t *comm, char *path, char **env);

/*	debug.c		*/
void debug_comm(comm_t *comm);

/*	pipe.c		*/
pipe_t *init_pipe(comm_t *in, comm_t *out);
void destroy_pipe(pipe_t *pipe);
int wait_for_it(pid_t pid);
int redirect_pipe_at_exec(comm_t *curr);
void debug_pid(char *s);
int run_pipeline(shell_t *shell, comm_t *comm);

static const char	prompt[]	=	"> ";
static const char	separators[]	=	" \t";
static const char	ign_delim[]	=	"";

enum {
	D_RIGHT,
	S_RIGHT,
	D_LEFT,
	S_LEFT,
	PIPE
};

enum {
	READ,
	WRITE
};

enum {
	OUT,
	IN
};

#endif