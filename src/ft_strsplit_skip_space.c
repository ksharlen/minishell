#include "minishell.h"

//!Считать ли пробелы словами????

static int	ft_num_str(const char *p_str, char sym)
{
	int		ret;

	ret = 0;
	if (p_str && *p_str)
	{
		while ((p_str = ft_strskipinv_sym(p_str, sym)) && *p_str)
		{
			if (p_str && *p_str)
			{
				++ret;
				p_str = ft_skip_word_sym(p_str, sym);
			}
		}
	}
	return (ret);
}

char	**ft_strsplit_skip_space(const char *str, char sym)
{
	//char 	**ret;
	int		num_str;

	num_str = ft_num_str(str, sym);
	ft_printf("num_str: %d\n", num_str);
	exit(EXIT_SUCCESS);
	return (NULL);
}
