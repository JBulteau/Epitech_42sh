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
#include <stdbool.h>

#define DEFAULT_PATH	"/usr/bin:/bin"

enum {
	S_LEFT,
	D_LEFT,
	S_RIGHT,
	D_RIGHT,
	PIPE
};

typedef enum {
	NOTHING,
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
typedef struct jobs_s jobs_t;

struct jobs_s {
	bool running;
	pid_t *pid_job;
	jobs_t *next;
};

struct alias_s {
	char *name;
	char *alias;
	bool loop;
	struct alias_s *nav[2];
};

typedef enum {
	NO_TYPE,
	NBR,
	STR
} type_t;

typedef union {
	char *content;
	int value;
} data_t;

typedef struct var_s {
	type_t type;
	char *name;
	data_t data;
} var_t;

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
	comm_t *next;
	comm_t **parenthesis;
	bool bg;
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
	var_t **vars;
	alias_t *aliases;
	history_t *history;
	int history_exec;
	int return_value;
} shell_t;

static const char	separators[]	=	" \t";
static const char	ign_delim[]	=	"";

/*	JARVIS		*/
int jarvis_corrector(comm_t *comm, char ***env);
int disp_modif(comm_t **arr);

/*	shel/exec/exec_jarvis.c	*/
int call_jarvis_rerun(shell_t *shell);
int exec_on_comm(comm_t *curr, shell_t *shell);
int exec_on_comm_arr(shell_t *shell);

/*	42rc/load42.c	*/
int ask_y_n(char *s, char *yes, char *no);
int load42(shell_t *shell);
int source_that_file(shell_t *shell, char *path);

/*	shell/alias/alias_comm.c	*/
int rm_alias(shell_t *shell, char *alias);
alias_t *dup_aliases(alias_t *alias);

/*	shell/alias/alias_struc.c	*/
alias_t *create_alias(char *name, char *alias, alias_t *prev);
char *concat_args(char **args);
int add_alias(char **args, shell_t *shell);
void free_aliases(alias_t *alias, int free_next);

/*	shell/builtins/alias.c		*/
int disp_aliases(alias_t *node);
int ptr_alias(comm_t *comm, shell_t *shell);
int ptr_unalias(comm_t *comm, shell_t *shell);

/*	shell/builtins/basic_bi.c	*/
int error_msg_exit(shell_t *shell, comm_t *comm);
int ptr_exit(comm_t *comm, shell_t *shell);
int is_builtin(char *name);
int exec_bi(comm_t *comm, shell_t *shell);
int ptr_builtins(comm_t *comm, shell_t *shell);

/*	shell/builtins/cd.c		*/
int change_dir(char pwd[2][PATH_MAX], char *newdir);
int ptr_cd(comm_t *comm, shell_t *shell);

/*	shell/builtins/echo.c		*/
int ptr_echo(comm_t *comm, shell_t *shell);

/*	shell/builtins/env.c		*/
int add_env_value(char ***env, char *value, char *var_pre);
int set_env_value(char ***env, char *var, char *value);
int ptr_env(comm_t *comm, shell_t *shell);
int ptr_setenv(comm_t *comm, shell_t *shell);
int ptr_unsetenv(comm_t *comm, shell_t *shell);

/*	shell/builtins/fg.c		*/
void set_node_running_false(pid_t pid);
int kill_cont_childs(jobs_t *node);
int ptr_fg(comm_t *comm, shell_t *shell);

/*	shell/builtins/history_exec.c	*/
int run_last(shell_t *shell);
int event_not_found(shell_t *shell, int n);
int run_n(shell_t *shell, int n);
int ptr_exec_his(comm_t *comm, shell_t *shell);

/*	shell/builtins/history.c	*/
history_t *create_new_case(char *s);
history_t *get_last(history_t *node);
int save_history(shell_t *shell, char *input);
void free_history(history_t *hist);
int ptr_history(comm_t *comm, shell_t *shell);

/*	shell/builtins/ptr_jobs.c	*/
char *get_proc_name_line(jobs_t *node);
int ptr_jobs(comm_t *comm, shell_t *shell);

/*	shell/builtins/repeat.c		*/
int ptr_repeat(comm_t *comm, shell_t *shell);

/*	shell/builtins/vars.c		*/
int ptr_unset(comm_t *comm, shell_t *shell);
int ptr_at(comm_t *comm, shell_t *shell);
int ptr_set(comm_t *comm, shell_t *shell);

/*	shell/exec/exec_pipe.c		*/
int run_not_last(shell_t *shell, comm_t *curr);
int run_and_fork(shell_t *shell, comm_t *curr);
int run_last_pipeline(shell_t *shell, comm_t *curr);
int run_pipeline(shell_t *shell, comm_t *comm);

/*	shell/exec/exec.c		*/
int exec_start(comm_t *comm);
int exec_end(comm_t *comm);
int run_that_comm(shell_t *shell, comm_t *comm);
int exec_loop(shell_t *shell, comm_t **comm_arr);
int exec_bin(comm_t *comm, char **env, shell_t *shell);

/*	shell/exec/redir_pipe.c		*/
int init_redir_pipe(comm_t *comm);
void close_in(comm_t *curr);

/*	shell/exec/run_bin.c		*/
int run_that(shell_t *shell);
int run_bin(comm_t *comm, char *path, char **env, shell_t *shell);

/*	shell/jobs/init_signal.c	*/
char *get_proc_name(pid_t pid);
int wait_for_it(pid_t pid);
int is_in_list(jobs_t *node, pid_t pid);

/*	shell/jobs/jobs.c		*/
jobs_t *find_node_job(void);
int get_nb_job(void);
jobs_t *new_node(void);
void remove_node(pid_t pid);
int add_pid_jobs(pid_t child);

/*	shell/jobs/sig_handlers.c	*/
void catch_ctrl_z(int sig);
void catch_ctrl_c(int sig);

/*	shell/jobs/signals.c		*/
int init_signal(void);
void free_jobs(void);

/*	shell/prompt/display.c		*/
int find_hanlder(char token);
int handle_prompt(shell_t *shell, char *prompt_var, int *i);
int printf_prompt(shell_t *shell);

/*	shell/prompt/handler_basic.c	*/
int ptr_modulo(shell_t *shell, char *input);

/*	shell/prompt/handler_colors.c	*/
int ptr_foreground(shell_t *shell, char *input);
int ptr_background(shell_t *shell, char *input);
int ptr_underline(shell_t *shell, char *input);
int ptr_bold(shell_t *shell, char *input);

/*	shell/prompt/handler_date.c	*/
char *get_day(int day);
int ptr_handle_date(shell_t *shell, char *input);
int ptr_handle_week(shell_t *shell, char *input);

/*	shell/prompt/handler_get_from_shell.c	*/
int ptr_handle_return(shell_t *shell, char *input);
int ptr_handle_pwd(shell_t *shell, char *input);
int ptr_handle_history(shell_t *shell, char *input);
int ptr_handle_jobs(shell_t *shell, char *input);

/*	shell/prompt/handler_time.c	*/
int ptr_handle_hour_24(shell_t *shell, char *input);
int ptr_handle_hour_12(shell_t *shell, char *input);
int ptr_handle_time_24(shell_t *shell, char *input);
int ptr_handle_time_12(shell_t *shell, char *input);
int ptr_handle_sec(shell_t *shell, char *input);

/*	shell/prompt/handler_vars.c	*/
int ptr_handle_env_var(shell_t *shell, char *input);
int ptr_handle_shell_var(shell_t *shell, char *input);

/*	shell/prompt/system_get.c	*/
int ptr_handle_host(shell_t *shell, char *input);
int ptr_handle_user(shell_t *shell, char *input);
int ptr_handle_root(shell_t *shell, char *input);
int ptr_handle_home(shell_t *shell, char *input);

/*	shell/redirections/d_left.c	*/
void loop_d_left(comm_t *comm);
int exec_d_left(comm_t *comm);
int end_d_left(comm_t *comm);

/*	shell/redirections/s_left.c	*/
int exec_s_left(comm_t *comm);
int end_s_left(comm_t *comm);

/*	shell/redirections/d_right.c	*/
int exec_d_right(comm_t *comm);
int end_d_right(comm_t *comm);

/*	shell/redirections/s_right.c	*/
int exec_s_right(comm_t *comm);
int end_s_right(comm_t *comm);

/*	shell/redirections/magic_quotes.c*/
char *get_str(int fd);
char *get_magic(shell_t *shell, char *comm);
history_t *dup_history(history_t *node);

/*	shell/shell_var/var.c		*/
var_t *init_var(void);
void free_var(var_t *var);
var_t **init_var_arr(void);
void debug_vars(var_t **arr);

/*	shell/shell_var/var_ptr_next.c	*/
int check_folder(char* path);
char *search_folder(char *folder, char *name);

/*	shell/shell_var/var_utils.c	*/
int find_var(var_t **arr, char *name);
char *get_var_str(var_t *var);
char *get_var(char **env, var_t **vars, char *name);
type_t get_type(char *content);
var_t **dup_vars(var_t **arr);

/*	shell/shell_var/var_edition.c	*/
int edit_var(var_t *var, char *content, char *name);
int unset_var(shell_t *shell, char *name);
var_t **set_var(var_t **arr, char *name, char *content);

/*	shell/shell_var/var_operations.c	*/

/*	shell/commands.c		*/
void free_comm(comm_t *comm);
comm_t *init_comm(void);
void free_comms(comm_t **comm);
int get_commidx(shell_t *shell, comm_t *comm);

/*	shell/debug.c			*/
void display_sep(sep_t separator);
void debug_comm(comm_t *comm);

/*	shell/display.c			*/
void disp_wrong_arch(char *str, int num);
void display_signal(int status);
int disp_prompt(shell_t *shell);

/*	shell/init.c	*/
int set_basic_env(shell_t *shell, char ***env);
int setup_default_env(char ***env, shell_t *shell);
int set_shlvl(char ***env);
int init_vars(shell_t *shell);

/*	shell/main.c			*/
int main(int ac, char **av, char **env);

/*	shell/pipe.c			*/
pipe_t *init_pipe(comm_t *in, comm_t *out);
void destroy_pipe(pipe_t *pipe);

/*	shell/redir.c			*/
void free_red(redir_t *red);
redir_t *init_redir(void);

/*	shell/search.c			*/
void disp_rights(char *name, int exists, int exec);
int search_local(char *name);
char *search_path(char **path, char *name);
char *get_env_var(char **env, char *var);
char **get_path(char **env, var_t **vars);

/*	shell/shell.c			*/
shell_t *init_shell(char **env);
void delete_shell(shell_t *shell);
shell_t *dup_shell(shell_t *shell);

/*	shell/utils.c			*/
int search_strtab(char **arr, char *to_find);
int check_is_dir(char *fn);
char **add_arr(char **arr, char *str, int free_arr);
void clean_exit(shell_t *shell, int exit_code);
char **clone_arr(char **arr);

/*	parsing/parsing.c	*/
comm_t **parsing(shell_t *shell);

/* Uncomment that when we will be able to do that
** #define __OSTYPE__ "Unknown"
** #define __MACHTYPE__ "Unknown"
** #define __VENDOR__ "Unknown"
** #ifdef __MACHTYPE__ && __OSTYPE__
**	#define __HOSTTYPE__ "Unknown"
** #endif
*/

extern jobs_t *list_jobs;

#endif