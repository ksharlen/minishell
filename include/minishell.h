/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:22:55 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/13 23:30:56 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <time.h>
# include <pwd.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <sys/stat.h>

# if __linux__
#  include <sys/wait.h>
# endif

# include "libft.h"
# include "internal_utilities.h"

# define PROG_NAME		"minishell"
# define SHELL			minishell
# define SHLVL			"SHLVL"

/*
**MINISHELL_ERRORS
*/
# define RET_ERROR	-1
# define E_OPEN		0
# define E_CLOSE	1
# define E_READ		2
# define E_OPENDIR	3
# define E_CLOSEDIR 4
# define E_READDIR	5
# define E_FORK		6
# define E_WAIT		7
# define E_SIGNAL	8
# define E_TIME		9
# define E_CTIME	10
# define E_WAITPID	11
# define E_KILL		12
# define E_GETCWD	13
# define E_MALLOC	14
# define E_CHDIR	15
# define E_STAT		16
# define E_FSTAT	17
# define E_LSTAT	18
# define E_GETPWUID	19

/*
**macro for entry shell
*/
# define TO_TIME		11
# define SIZE_TIME 		8
# define MAX_UNAME		255
# define MAX_SIZE_PATH	32767
# define COLOR_DIR		"\e[36m"
# define COLOR_UNAME	"\e[33m"
# define COLOR_DEFAULT	"\e[0m"
# define INF			1

/*
**ERRORS
*/
# define PERM_DENIED		"permission denied:"
# define NO_SUCH_F_OR_D		"no such file or directory:"
# define STR_NOT_IN_PWD		"string not in pwd:"
# define ILLEGAL_OPT		"illegal option --e"
# define NOT_FOUND_CMD		"command not found:"
# define FILE_TO_LONG		"file name too long:"

/*
**SIG_ERRORS
*/
# define FORMAT "%v[%s]    %d %s  %s\n"
# define PRINT_S(l, p, e, f) ft_printf(FORMAT, STDERR, l, p, e, f)
# define PRINT_SIG_ERR(lvl, pid, err, file) PRINT_S(lvl, pid, err, file)
# define ESIG	"Segmentation fault"
# define EBUS	"Bus error"
# define QUIT	"Quit"
# define EABR	"Abort trap"
# define FPOT	"Floating point exception"

/*
**MSHELL_ERRORS
*/
# define MS_STR "%v%s: %s %s\n"
# define PRINT(p_nm, e_nm, out) ft_printf(MS_STR, STDERR, p_nm, e_nm, out)
# define PRINT_ERROR(p_nm, e_nm, out) PRINT(p_nm, e_nm, out)
# define CMD_NOT_FOUND(p_nm) PRINT_ERROR(PROG_NAME, NOT_FOUND_CMD, p_nm)

/*
**PATH
*/
# define UTILITIES				"utilities"
# define MHISTORY 				".minishell_history"
# define MRC 					".minishellrc"
# define KEY_LAST_CMD_MHISTORY	"KEY"

/*
**OTHER
*/
# define COMMAND_SPLIT		';'
# define PATH_SPLIT			':'
# define SPLIT_COMMANDS 	ft_strsplit_skip_space
# define NEW_PROCESS		fork
# define CMD_NAME			argv[0]
# define CHILD_PROCESS		0
# define NUM_INTERNAL_CMDS	7
# define NUMBERS			"0123456789"
# define EXP_PATH			extern struct s_path g_path
# define EXP_ENV			extern char **environ

# define P_INT_CMD	path_internal_cmd
# define P_MSRC		path_mshellrc
# define P_MSHIST	path_mshell_history

/*
**MINISHELL_HISTORY
*/
# define SIZE_DATE		24

EXP_ENV;
EXP_PATH;

typedef unsigned long long	t_key;
typedef unsigned int		t_error;

enum			e_str
{
	STDIN = STDIN_FILENO,
	STDOUT = STDOUT_FILENO,
	STDERR = STDERR_FILENO
};

enum			e_find
{
	NOT_FOUND = -1,
	FOUND_INTERNAL_CMD,
	FOUND_SHELL_DIR,
	FOUND_PATH_ENV,
	FOUND,
	FOUND_EXIT,
};

struct			s_entry
{
	char time[SIZE_TIME + 1];
	char uname[MAX_UNAME];
	char curr_dir[MAX_SIZE_PATH];
};

struct			s_path
{
	char	path_internal_cmd[MAX_SIZE_PATH + 1];
	char	path_mshellrc[MAX_SIZE_PATH + 1];
	char	path_mshell_history[MAX_SIZE_PATH + 1];
};

typedef struct	s_argv
{
	char			**argv;
	int				argc;
	struct s_argv	*next;
}				t_argv;

struct			s_key_data
{
	int			fd_ms_history;
	int			key;
	char		*key_str;
	char		date_ex_cmd[SIZE_DATE + 1];
};

/*
**MAIN_FUNCa
*/
void			minishell_greeting(void);
char			*minishell_read_stdio(void);
t_argv			*minishell_parse_str(const char *str_for_parse);
int				minishell_command_execution(t_argv *beg);
int				minishell_command_search(const char *cmd, char *path_ex);
void			garbage_collector_internal(t_argv **beg);
void			minishell_push_minishell_history(const char *str_stdio,
	struct s_key_data *k_data);

void			list_add_end(t_argv **beg, char *cmd_argv);
int				find_in_the_var_path_env(const char *path_env,
	const char *cmd, char *path_ex);
void			strddel(char ***del);
void			push_path(const char *cmd, const char *path, char *path_ex);
int				search_path(const char *path, const char *cmd, char *path_ex);
int				execute_cmd(char *const argv[], const char *path_cmd);
void			minishell_handler(int sig);

void			getkey_internal(struct s_key_data *key);

/*
**MSHELL_HISTORY
*/
void			minishell_history_init(struct s_key_data *k_data);
void			minishell_history_close(struct s_key_data *k_data);

/*
**ERRORS
*/
void			err_str(t_error merror, const char *add_text);
void			err_exit(t_error merror, const char *add_text);

/*
**INIT
*/
void			minishell_paths_init(void);

/*
**SIGNALS
*/
void			status_child(int status_child,
	pid_t pid_child, const char *path_cmd);
void			handler_parrent(int sig);
void			handler_child(int sig);
void			ignore_signals(int sig);
void			minishell_signals(void (*handler)(int));
void			status_child(const int status_child,
	const pid_t pid_child, const char *path_cmd);

/*
**GETERS
*/
int				mshell_getpwd(char *buf);
int				mshell_getoldpwd(char *buf);
int				mshell_gethomedir(char *buf);

#endif
