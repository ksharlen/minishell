#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <time.h>
# include <pwd.h>
# include <signal.h>

# if __linux__
#	include <sys/wait.h>
#	include <sys/types.h>
# endif

# include "libft.h"

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

# define COMMAND_SPLIT	';'

# define SPLIT_COMMANDS ft_strsplit_skip_space

enum		e_stdstream
{
	STDIN,
	STDOUT
};

// enum		e_gnl
// {
// 	NOTHING_READ,
// 	HAS_BEEN_READ,
// 	READ_ERROR
// };

struct		s_entry
{
	char time[SIZE_TIME + 1];
	char uname[MAX_UNAME];
	char curr_dir[MAX_SIZE_PATH];
};

struct		s_argv
{
	char	**parsed_cmds;
}

void	minishell_greeting(void);
char	*minishell_read_stdio(void);
char	**minishell_parse_str(const char *str_for_parse);
void	minishell_command_execution(char *const commands[]);

#endif
