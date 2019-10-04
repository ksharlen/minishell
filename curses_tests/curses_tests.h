#ifndef CURSES_TESTS_H
# define CURSES_TESTS_H

# include <sys/types.h>
# include <stdio.h>
# include <stdlib.h>

# include <unistd.h>
# include <ncurses.h>
# include <fcntl.h>
# include <string.h>

# define SIZE_BUF 255
# define USER "ksharlen"
# define PRINT_U() printw("%s $>", USER)
# define PATH "/bin/"

# define CHECK_COMBO_KEY(key) ((key) == 3 || (key) == 4 || (key) == 12 || (key) == 26 || (key) == 28 || key == '\n')

typedef struct	s_argv
{
	char			**argv;
	int				argc;
	struct s_argv	*next;
}				t_argv;

t_argv		*minishell_parse_str(const char *str_for_parse);

#endif