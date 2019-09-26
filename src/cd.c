/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:35:31 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 22:35:33 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void error(void)
{
	exit(EXIT_SUCCESS);
}

static void	get_new_path(char *old_dir)
{
	char	*new_dir;
	int		i;
	int		new_len;

	i = -1;
	new_len = 0;
	while (old_dir[new_len])
		++new_len;
	while (old_dir[new_len] != '/')
		--new_len;
	if (!(new_dir = (char*)malloc(sizeof(char) * (new_len + 1))))
		exit(0);
	while (++i < new_len)
		new_dir[i] = old_dir[i];
	new_dir[i] = '\0';
	if (chdir(new_dir))
		error();
	my_setenv("PWD", new_dir, old_dir);
	free(new_dir);
}

static int	check_dots_and_hyphen(char *const argv[], char *cur_dir, char *const env[])
{
	char *tmp;
	int n;

	n = -1;
	while (++n)
		if (ft_strstr(env[n], "OLDPWD"))
			tmp = ft_strdup(env[n]);
	if (ft_strequ(argv[1], "."))
		return (0);
	else if (ft_strequ(argv[1], ".."))
	{
		get_new_path(cur_dir);
		return (0);
	}
	else if (ft_strequ(argv[1], "-"))
	{
		my_setenv("PWD", tmp, cur_dir);
		return (0);
	}
	return (1);
}

int			cd(char *const argv[], char *const env[])
{
	char	cur_dir[MAX_SIZE_PATH];
	char	*home_dir;
	int		n;

	n = -1;
	while (++n)
		if (ft_strstr(env[n], "HOME"))
			home_dir = ft_strdup(ft_strchr(env[n], '='));
	if (!(getcwd(cur_dir, MAX_SIZE_PATH)))
		error();
	if (!argv[1] || ft_strequ(argv[1], "~") || ft_strequ(argv[1], "--"))
	{
		if (chdir(home_dir))
			exit(0);
		set_env(argv, env, cur_dir);
	}
	else if (argv[2])
		error();
	else
	{
		if (check_dots_and_hyphen(argv, cur_dir, env))
		{
			chdir(argv[1]);
			set_env(argv, env, cur_dir);
		}
	}
	return (0);
}
