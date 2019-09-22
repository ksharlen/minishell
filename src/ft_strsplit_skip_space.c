#include "minishell.h"

//!Считать ли пробелы словами????

static int	ft_find_sym(const char *p_str, char sym)
{
	int			ret;

	if (*p_str)
	{
		if (!(p_str = ft_strchr(p_str, sym)))
			return (1);
		ret = 1;
		while (*p_str)
		{
			p_str = ft_strchr(p_str, sym);
			p_str = *p_str ? (p_str + 1) : p_str;
			//*p_str ? ++p_str : 0;
			//ft_printf("sym: %c\n", *p_str);
			++ret;
		}
		return (ret);
	}
	return (0);
}

char	**ft_strsplit_skip_space(const char *str, char sym)
{
	char 	**ret;
	int		num_str;

	P_UNUSED(ret);
	num_str = ft_find_sym(str, sym);
	ft_printf("num_str: %d\n", num_str);
	exit(EXIT_SUCCESS);
	return (NULL);
}
