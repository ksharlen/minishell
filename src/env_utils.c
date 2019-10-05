/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:10:52 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/02 21:52:05 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int			my_unsetenv(char *key)
{
	unsetenv(key);//!need to defense
	return (0);
}

int			my_setenv(char *key, char *value, char *old_pwd)
{
	if (ft_strequ(key, "PWD"))
	{
		setenv(key, value, 1);//!need to defense
		setenv("OLDPWD", old_pwd, 1);//!need to defense
	}
	else
		setenv(key, value, 1);//!need to defense
	return (0);
}

static int	check_key_for_env(char *const argv[])
{
	if (ft_strequ(argv[1], "-i") || ft_strequ(argv[1], "--ignore-environment"))
	{
		//!! place for fork)))
		return (1);
	}
	else if (ft_strequ(argv[1], "-u") || ft_strstr(argv[1], "--unset="))
	{
		if (ft_strequ(argv[1], "-u"))
			my_unsetenv(argv[2]);
		else
			my_unsetenv(ft_strchr(argv[1], '=') + 1);
		return (1);
	}
	else if (ft_strstr(argv[1], "--") || ft_strstr(argv[1], "-"))
	{
		PRINT_ERROR(argv[0], ILLEGAL_OPT, argv[1]);
		ft_printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
		ft_printf("           [name=value ...] [utility [argument ...]]\n");
		return (-1);
	}
	return (0);
}

int			env(int argc, char *argv[], char *env[])
{
	int		n;
	char	**key_and_value;

	P_UNUSED(argc);
	n = -1;
	if (!argv[1] || ft_strequ(argv[1], "-v"))
	{
		while (env[++n])
			ft_printf("%s\n", env[n]);
		return (0);
	}
	else
	{
		if (!check_key_for_env(argv))
		{
			key_and_value = ft_strsplit(argv[1], '=');
			my_setenv(key_and_value[0], key_and_value[1], NULL);
		}
		return (0);
	}
	return (-1);
}
