/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operation_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/07 00:27:17 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/08 16:09:32 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static void	delete_name(char *const *need_delete)
{
	if (need_delete)
		while (*need_delete)
			minishell_unsetenv(*need_delete++);
}

char *const	*u_flag(char *const argv[])
{
	char	**split;

	if (argv && *argv)
	{
		if (!ft_strcmp(*argv, "-S"))
		{
			++argv;
			split = s_flag((char *)*argv);
			delete_name(split);
			//!Зафришить
		}
		else
			minishell_unsetenv(*argv);
		++argv;
	}
	return (argv);
}

static void		change_value(char *const *need_add)
{
	struct s_nameval nval;

	if (need_add && *need_add)
	{
		while (*need_add)
		{
			nval = split_name_val(*need_add);
			//!зафришить
			minishell_setenv(nval.name, nval.value, FLAG_ON);
			ft_strdel(&nval.name);
			ft_strdel(&nval.value);
			++need_add;
		}
	}
}

char	*const*	change_value_name(char *const argv[])
{
	char 		**split;

	split = NULL;
	if (*argv && !ft_strcmp(*argv, "-S"))
	{
		++argv;
		if (*argv && ft_strtabchr((char *)*argv, '='))
		{
			split = s_flag(*argv);
			change_value(split);
		}
	}
	else
	{
		if (*argv && ft_strtabchr(*argv, '='))
		{
			change_value((char *const *)*&argv);
			++argv;
		}
	}
	return (argv);
	//!Зафришить!!!!!!!!!!!!!!!!!!!
}

char	**s_flag(const char *str)
{
	char **split;

	split = NULL;
	if (str)
		split = ft_strsplit_skip_space((char *)str, ' ');
	return (split);
}
