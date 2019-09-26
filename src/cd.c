/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 20:15:30 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 22:33:53 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
		error(new_dir);
	my_setenv("PWD", new_dir, old_dir);
	free(new_dir);
}

static int	check_dots_and_hypen(t_argv *beg, char *cur_dir, char **env)
{
	char *tmp;
	int n;

	n = -1;
	while (++n)
		if (ft_strstr(env[n], "OLDPWD"))
			tmp = ft_strdup(env[n]);
	if (ft_strequ(beg->argv[1], "."))
		return (0);
	else if (ft_strequ(beg->argv[1], ".."))
	{
		get_new_path(cur_dir);
		return (0);
	}
	else if (ft_strequ(beg->argv[1], "-"))
	{
		mt_setenv("PWD", tmp, cur_dir);
		return (0);
	}
	return (1);
}	

int			get_cd(t_argv *beg, char **env)
{
	char	cur_dir[MAX_SIZE_PATH];
	char	*home_dir;
	int		n;

	n = -1;
	while (++n)
		if (ft_strstr(env[n], "HOME"))
			home_dir = ft_strdup(ft_strchr(env[n], '='));
	if (!(getcwd(cur_dir, MAX_SIZE_PATH)))
		error(cur_dir);
	if (!beg->argv[1] || ft_strequ(beg->argv[1], "~") || ft_strequ(beg->argv[1], "--"))
	{
		if (chdir(home_dir))
			exit(0);
		set_env(beg, env, cur_dir);
	}
	else if (beg->argv[2])
		error(cur_dir);
	else
	{
		if (check_dots_and_hyphen(beg, cur_dir, env))
		{
			chdir(beg->argv[1]);
			set_env(beg, env, cur_dir);
		}
	}
	return (0);
}
