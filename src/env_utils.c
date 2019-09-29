/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:10:52 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/29 17:22:28 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MYERROR 1

void		my_unsetenv(char *key)
{
	if (unsetenv(key))
		exit(0);
}

void		my_setenv(char *key, char *value, char *old_pwd)
{
	int n;

	n = -1;
	if (ft_strequ(key, "PWD"))
	{
		if (setenv(key, value, 1))
			exit(0);
		if (setenv("OLDPWD", old_pwd, 1))
			exit(0);
	}
	else
	{
		if (setenv(key, value, 1));
			exit(0);
	}
}

static int	check_key_for_env(char *const argv[], char *const env[])
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
			my_unsetenv(ft_strsub(argv[1], *argv[1] - ft_strrchr(argv[1], '=')));
		return (1);
	}
	else if (ft_strequ(argv[1], "--version"))
	{
		return (1);
	}
	else
	{
		PRINT_ERROR(argv[0], "illegal opiton -- e", NULL);
		ft_printf("usage: env [-iv] [-P utilpath] [-S string] [-u name]\n");
		ft_printf("           [name=value ...] [utility [argument ...]]\n");
		return (-1);
	}
	return (0);
}

int			env(char *const argv[], char *const env[])
{
	int n;

	n = -1;
	if (!argv[1] || ft_strequ(argv[1], "-v"))
	{
		while (env[++n])
			ft_printf("%s\n", env[n]);
		return (0);
	}
	else
	{
		if (!check_key_for_env(argv, env))
			my_setenv(argv[1], argv[2], NULL);
		return (0);
	}
	return (-1);
}
