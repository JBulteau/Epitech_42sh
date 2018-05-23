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
	bool fg;
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

/*	42rc/load42.c	*/
int ask_y_n(char *s, char *yes, char *no);
int load42(shell_t *shell);

/*	shell/alias/alias_comm.c	*/
int rm_alias(shell_t *shell, char *alias);
int update_aliases(shell_t *shell, comm_t *comm, int remove, int skip_curr);

/*	shell/alias/alias_struc.c	*/
alias_t *create_alias(char *name, char*alias, alias_t *prev);
int add_alias(char **args, shell_t *shell);
void free_aliases(alias_t *alias, int free_next);

/*	shell/alias/alias.c		*/

/*	shell/builtins/alias.c		*/
/*	shell/builtins/basic_bi.c	*/
int error_msg_exit(shell_t *shell, comm_t *comm);
int is_builtin(char *name);
int exec_bi(comm_t *comm, shell_t *shell);

/*	shell/builtins/cd.c		*/
/*	shell/builtins/echo.c		*/
/*	shell/builtins/env.c		*/
int add_env_value(char ***env, char *value, char *var_pre);
int set_env_value(char ***env, char *var, char *value);

/*	shell/builtins/fg.c		*/
/*	shell/builtins/history_exec.c	*/
/*	shell/builtins/history.c	*/
history_t *create_new_case(char *s);
history_t *get_last(history_t *node);
int save_history(shell_t *shell, char *input);
void free_history(history_t *hist);

/*	shell/redirections/d_left.c	*/
/*	shell/redirections/s_left.c	*/
/*	shell/redirections/d_right.c	*/
/*	shell/redirections/s_right.c	*/

/*	shell/shell_var/var.c		*/
var_t *init_var(void);
void free_var(var_t *var);
var_t **init_var_arr(void);
void disp_vars(var_t **arr);
var_t **try_vars(void);

/*	shell/shell_var/var_utils.c	*/
int find_var(var_t **arr, char *name);
type_t get_type(char *content);
void clean_exit(shell_t *shell, int exit_code);
char *get_var_str(var_t *var);

/*	shell/shell_var/var_edition.c	*/
int edit_var(var_t *var, char *content, char *name);
var_t **set_var(var_t **arr, char *name, char *content);

/*	shell/commands.c		*/
void free_comm(comm_t *comm);
comm_t *init_comm(void);
void free_comms(comm_t **comm);
int get_commidx(shell_t *shell, comm_t *comm);
int run_that(shell_t *shell);

/*	shell/debug.c			*/
/*	shell/display.c			*/
void disp_wrong_arch(char *str, int num);
void display_signal(int status);
int disp_prompt(shell_t *shell);

/*	shell/init.c	*/
int set_basic_env(shell_t *shell, char ***env);
int setup_default_env(char ***env, shell_t *shell);
int set_shlvl(char ***env);
int init_vars(shell_t *shell);

/*	shell/exec_pipe.c		*/
int run_not_last(shell_t *shell, comm_t *curr);
int run_last_pipeline(shell_t *shell, comm_t *curr);
int run_pipeline(shell_t *shell, comm_t *comm);

/*	shell/exec.c			*/
int exec_start(comm_t *comm);
int exec_end(comm_t *comm);
int exec_loop(shell_t *shell);
int exec_bin(comm_t *comm, char **env,shell_t *shell);
int run_bin(comm_t *comm, char *path, char **env, shell_t *shell);
/*	shell/init_signal.c		*/
char* get_proc_name(pid_t pid);
void catch_ctrl_z(int sig);
void catch_ctrl_c(int sig);
int init_signal(void);
int wait_for_it(pid_t pid);

/*	shell/jobs.c			*/
jobs_t *find_node_job(void);
int get_nb_job(void);
jobs_t *new_node(void);
void remove_node(void);
int add_pid_jobs(pid_t child);
void set_node_running_false(void);


/*	shell/main.c			*/
int main(int ac, char **av, char **env);

/*	shell/parsing.c			*/
int is_tk(char *input);
char *go_next_w(char *input, const char *separator);
int parse_command(char *input, comm_t *comm);
comm_t **full_parse(char *input);

/*	shell/pipe.c			*/
pipe_t *init_pipe(comm_t *in, comm_t *out);
void destroy_pipe(pipe_t *pipe);

/*	shell/redir_pipe.c		*/
int init_redir_pipe(comm_t *comm);
void close_in(comm_t *curr);

/*	shell/redir.c			*/
void free_red(redir_t *red);
redir_t *init_redir(void);

/*	shell/search.c			*/
void disp_rights(char *name, int exists, int exec);
int search_local(char *name);
char *search_path(char **path, char *name);
char *get_env_var(char **env, char *var);
char **get_path(char **env);

/*	shell/shell.c			*/
char **clone_arr(char **arr);
shell_t *init_shell(char **env);
void delete_shell(shell_t *shell);

/*	shell/utils.c			*/
int search_strtab(char **arr, char *to_find);
int check_is_dir(char *fn);
char **add_arr(char **arr, char *str, int free_arr);
comm_t **parsing(char *buffer);

/*	shell/infos.c			*/
int set_infos(char ***env);

/*	prompt/display.c	*/
int printf_prompt(shell_t *shell);

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