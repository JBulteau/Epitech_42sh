/*
** EPITECH PROJECT, 2017
** minishell.c
** File description:
** Header for minishell
*/

#ifndef __MINI__
#define __MINI__

#include <stdlib.h>
#include <linux/limits.h>

extern pid_t *pid_job;

enum {
	D_RIGHT,
	S_RIGHT,
	D_LEFT,
	S_LEFT,
	PIPE
};

typedef enum {
	NONE,
	THEN,
	OR
} sep_t;

enum {
	READ,
	WRITE
};

enum {
	OUT,
	IN
};

enum {
        PREV,
        NEXT
};

typedef struct redir_s redir_t;
typedef struct comm_s comm_t;
typedef struct pipe_s pipe_t;
typedef struct alias_s alias_t;

struct alias_s {
	char *name;
        char *alias;
        struct alias_s *nav[2];
};

typedef struct history_s {
	char *data;
	struct history_s *next;
} history_t;

struct redir_s {
	char *target;
	int fd[2];
};

struct comm_s {
	char **argv;
	sep_t separator;
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
	alias_t *aliases;
	history_t *history;
	int history_exec;
	int return_value;
} shell_t;

char **add_arr(char **arr, char *str, int free_arr);
char **clone_arr(char **arr);
comm_t **full_parse(char *input);
char **get_path(char **env);
alias_t *create_alias(char *name, char*alias, alias_t *prev);
history_t *create_new_case(char *s);
char *get_env_var(char **env, char *var);
history_t *get_last(history_t *node);
char *go_next_w(char *input, const char *separator);
char *handle_d_left(char *input, comm_t *comm);
char *handle_d_right(char *input, comm_t *comm);
char *handle_pipe(char *input, comm_t *comm);
char *handle_s_left(char *input, comm_t *comm);
char *handle_s_right(char *input, comm_t *comm);
comm_t *init_comm(void);
pipe_t *init_pipe(comm_t *in, comm_t *out);
redir_t *init_redir(void);
shell_t *init_shell(char **env);
char *search_path(char **path, char *name);
int add_alias(char **args, shell_t *shell);
int add_env_value(char ***env, char *value, char *var_pre);
int add_to_pid(pid_t child);
int ask_y_n(char *s, char *yes, char *no);
void catch_ctrl_c(int sig);
void catch_ctrl_z(int sig);
int change_dir(char pwd[2][PATH_MAX], char *newdir);
int check_is_dir(char *fn);
void close_in(comm_t *curr);
void debug_comm(comm_t *comm);
void delete_shell(shell_t *shell);
void destroy_pipe(pipe_t *pipe);
int disp_aliases(alias_t *node);
void disp_prompt(void);
void disp_rights(char *name, int exists, int exec);
void disp_wrong_arch(char *str, int num);
void display_signal(int status);
int end_d_left(comm_t *comm);
int end_d_right(comm_t *comm);
int end_s_left(comm_t *comm);
int end_s_right(comm_t *comm);
int error_msg_exit(shell_t *shell, comm_t *comm);
int exec_bi(comm_t *comm, shell_t *shell);
int exec_bin(comm_t *comm, char **env);
int exec_d_left(comm_t *comm);
int exec_d_right(comm_t *comm);
int exec_end(comm_t *comm);
int exec_loop(shell_t *shell);
int exec_s_left(comm_t *comm);
int exec_s_right(comm_t *comm);
int exec_start(comm_t *comm);
int find_last_pid(void);
void free_aliases(alias_t *alias, int free_next);
void free_comms(comm_t **comm);
void free_comm(comm_t *comm);
void free_history(history_t *hist);
void free_red(redir_t *red);
char* get_proc_name(pid_t pid);
int init_redir_pipe(comm_t *comm);
int init_signal(void);
int is_builtin(char *name);
int is_tk(char *input);
int load42(shell_t *shell);
void loop_d_left(comm_t *comm);
int main(int ac, char **av, char **env);
int parse_command(char *input, comm_t *comm);
int ptr_alias(comm_t *comm, shell_t *shell);
int ptr_cd(comm_t *comm, shell_t *shell);
int ptr_env(comm_t *comm, shell_t *shell);
int ptr_exit(comm_t *comm, shell_t *shell);
int ptr_fg(comm_t *comm, shell_t *shell);
int ptr_history(comm_t *comm, shell_t *shell);
int ptr_setenv(comm_t *comm, shell_t *shell);
int ptr_unsetenv(comm_t *comm, shell_t *shell);
int remove_last_pid(void);
int replace_alias(alias_t *node, comm_t *comm);
int rm_alias(shell_t *shell, char **av);
void rm_one_alias(char *alias, alias_t *current, shell_t *shell);
int run_bin(comm_t *comm, char *path, char **env);
int run_last_pipeline(shell_t *shell, comm_t *curr);
int run_not_last(shell_t *shell, comm_t *curr);
int run_pipeline(shell_t *shell, comm_t *comm);
int save_history(shell_t *shell, char *input);
int search_local(char *name);
int search_strtab(char **arr, char *to_find);
int set_env_value(char ***env, char *var, char *value);
int wait_for_it(pid_t pid);

static const char	prompt[]	=	"> ";
static const char	separators[]	=	" \t";
static const char	ign_delim[]	=	"";

#endif
