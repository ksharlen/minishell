/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
<<<<<<< HEAD
/*   Created: 2019/09/27 21:13:02 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/27 21:13:04 by rloraine         ###   ########.fr       */
=======
/*   Created: 2019/09/26 21:22:55 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 17:55:49 by ksharlen         ###   ########.fr       */
>>>>>>> ksharlen
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

/*
**ERRORS
*/
# define NOT_FOUND_CMD		"command not found:"
# define N_TOO_LONG			"file name too long:"
# define PRINT(p_name, e_str, out) ft_printf("%s: %s %s\n", p_name, e_str, out)
// # define PRINT(x) ft_printf("%s: %s %s\n", PROGRAM_NAME, NOT_FOUND_CMD, (x))
// # define CMD_NOT_FOUND(x) PRINT(x)
// # define N_TOO_LNG(p_name, )


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
# define SIZE_DATE		25

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
	FOUND_OUR_DIR,
	FOUND_PATH_ENV,
	FOUND_INTERNAL
};

struct			s_entry
{
	char time[SIZE_TIME + 1];
	char uname[MAX_UNAME];
	char curr_dir[MAX_SIZE_PATH];
};

struct			s_minishell_history
{
	char	date_ex_cmd[SIZE_DATE + 1]; //!Тут подумать про размер
	t_key	key;
};

typedef struct	s_argv
{
	char			**argv;
	int				argc;
	struct s_argv	*next;
}				t_argv;

void			minishell_greeting(const char *home_dir);
char			*minishell_read_stdio(void);
t_argv			*minishell_parse_str(const char *str_for_parse);
void			minishell_command_execution(t_argv *beg, char *const env[]);
void			list_add_end(t_argv **beg, char *cmd_argv);
void			garbage_collector_internal(t_argv **beg);
int				minishell_command_search(const char *cmd, char *path_ex);
int				find_in_the_var_path_env(const char *path_env,
	const char *cmd, char *path_ex);
void			strddel(char ***del);
void			push_path(const char *cmd, const char *path, char *path_ex);
int				search_path(const char *path, const char *cmd, char *path_ex);
void			minishell_push_minishell_history(const char *str_stdio, t_key *key);

t_key			getkey_internal(void);

/*
**	----UTILS----
*/
int			cd(char *const argv[], char *const env[]);
void		my_setenv(char *key, char *value, char *old_pwd);
void		my_unsetenv(char *key);
void		pwd(char *const *argv[], char *const env[]);

#endif
