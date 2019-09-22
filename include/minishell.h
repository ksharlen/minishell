#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <time.h>

# if __linux__
#	include <sys/wait.h>
# endif

# include "libft.h"

char	**ft_strsplit_skip_space(const char *str, char sym);

#endif
