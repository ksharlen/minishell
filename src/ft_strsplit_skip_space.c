#include "minishell.h"

static int	ft_num_str(const char *p_str, char sym)
{
	int		ret;

	ret = 0;
	if (p_str && *p_str)
	{
		while (p_str && *p_str)
		{
			p_str = ft_skiptabs(p_str);
			if (p_str && *p_str && (*p_str != sym))
				++ret;
			p_str = ft_skip_before(p_str, sym);
		}
	}
	return (ret);
}

char	**ft_strsplit_skip_space(const char *str, char sym)
{
	int		num_str;

	num_str = ft_num_str(str, sym);
	ft_printf("num_str: %d\n", num_str);
	exit(EXIT_SUCCESS);
	return (NULL);
}
