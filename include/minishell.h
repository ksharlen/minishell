/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 21:22:55 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/30 16:38:49 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <signal.h>
# include <dirent.h>
# include <fcntl.h>

# if __linux__
#  include <sys/wait.h>
#  include <sys/types.h>
# endif

# include "libft.h"

# define PROG_NAME		"minishell"
# define SHELL			minishell

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
# define NOT_FOUND_CMD		"command not found:"
# define FILE_TO_LONG		"file name too long:" //worging for file and cmd

# define PRINT(p_name, e_name, out) ft_printf("%s: %s %s\n", p_name, e_name, out)
# define PRINT_ERROR(p_name, e_name, out) PRINT(p_name, e_name, out)
# define CMD_NOT_FOUND(p_name) PRINT_ERROR(PROG_NAME, NOT_FOUND_CMD, p_name)
//# define PRINT(x) ft_printf("%s: %s %s\n", PROGRAM_NAME, NOT_FOUND_CMD, (x))
//# define CMD_NOT_FOUND(x) PRINT(x)

/*
**PATH
*/
# define INTERNAL_DIR_CMD	"/Users/ksharlen/git_clones/minishell/utilities"
# define MHISTORY "/Users/ksharlen/git_clones/minishell/.minishell_history"
# define MRC	"/Users/ksharlen/git_clones/minishell/.minishellrc"
# define KEY_LAST_CMD_MHISTORY "KEY"

/*
**OTHER
*/
# define COMMAND_SPLIT	';'
# define PATH_SPLIT		':'
# define SPLIT_COMMANDS ft_strsplit_skip_space
# define NEW_PROCESS	fork
# define CMD_NAME		argv[0]
# define CHILD_PROCESS	0
# define NUM_INTERNAL_CMDS	6
# define NUMBERS		"0123456789"

/*
**MINISHELL_HISTORY
*/
# define SIZE_DATE		24

extern char	*g_internal_commands[];

typedef unsigned long long t_key;

enum			e_stdstream
{
	STDIN,
	STDOUT
};

enum			e_find
{
	NOT_FOUND = -1,
	FOUND_INTERNAL_CMD,
	FOUND_SHELL_DIR,
	FOUND_PATH_ENV,
	FOUND,
	FOUND_EXIT
};

struct			s_entry
{
	char time[SIZE_TIME + 1];
	char uname[MAX_UNAME];
	char curr_dir[MAX_SIZE_PATH];
};

// struct			s_minishell_history
// {
// 	char	date_ex_cmd[SIZE_DATE + 1]; //!Тут подумать про размер
// 	t_key	key;
// };

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

void			minishell_greeting(const char *home_dir);
char			*minishell_read_stdio(void);
t_argv			*minishell_parse_str(const char *str_for_parse);
int				minishell_command_execution(t_argv *beg, char *const env[]);
void			list_add_end(t_argv **beg, char *cmd_argv);
void			garbage_collector_internal(t_argv **beg);
int				minishell_command_search(const char *cmd, char *path_ex);
int				find_in_the_var_path_env(const char *path_env,
	const char *cmd, char *path_ex);
void			strddel(char ***del);
void			push_path(const char *cmd, const char *path, char *path_ex);
int				search_path(const char *path, const char *cmd, char *path_ex);
void			minishell_push_minishell_history(const char *str_stdio, struct s_key_data *k_data);

void			getkey_internal(struct s_key_data *key);

/*
**MSHELL_HISTORY
*/
void			minishell_history_init(struct s_key_data *k_data);
void			minishell_history_close(struct s_key_data *k_data);


#endif
