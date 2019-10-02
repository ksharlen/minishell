/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:35:31 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/02 21:31:17 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static char	*find_env(char *const env[], char *key)
{
	char	*tmp;
	int		n;

	n = -1;
	while (env[++n])
		if (ft_strstr(env[n], key))
			tmp = ft_strdup(ft_strchr(env[n], '/'));//!need to defense
	return (tmp);
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
	new_dir = (char*)malloc(sizeof(char) * (new_len + 1));//!need to defense
	while (++i < new_len)
		new_dir[i] = old_dir[i];
	new_dir[i] = '\0';
	chdir(new_dir);//!need to defense
	my_setenv("PWD", new_dir, old_dir);
	free(new_dir);
}

static int	check_dots_and_hyphen(char *const argv[], char *cur_dir,\
	char *const env[])
{
	char *tmp;

	tmp = find_env(env, "OLDPWD=");
	if (ft_strequ(argv[1], "."))
		return (0);
	else if (ft_strequ(argv[1], ".."))
	{
		get_new_path(cur_dir);
		return (0);
	}
	else if (ft_strequ(argv[1], "-"))
	{
		chdir(tmp);//!need to defense
		ft_printf("%s\n", tmp);
		my_setenv("PWD", tmp, cur_dir);
		free(tmp);
		return (0);
	}
	return (1);
}

int			check_dir_and_path_for_err(char *const argv[])
{
	int i;
	int check;

	i = -1;
	check = 0;
	while (argv[1][++i] && ++check)
	{
		if (i == MAX_SIZE_PATH)
			PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, argv[1]);
		if (argv[1][i] == '/')
		{
			if (check > 255)
				PRINT_ERROR_AND_RET(argv[0], FILE_TO_LONG, argv[1]);
		}
	}
	if (!access(argv[0], F_OK))
	{
		if (!access(argv[0], R_OK) && !access(argv[0], W_OK))
			return (0);
		else
			PRINT_ERROR_AND_RET(argv[0], PERM_DENIED, argv[1]);
	}
	else if (access(argv[0], F_OK))
		PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, argv[1]);
	return (0);
}

int			cd(int argc, char *argv[], char *env[])
{
	char	cur_dir[MAX_SIZE_PATH + 1];
	char	*home_dir;
	char	*full_path;

	P_UNUSED(argc);
	full_path = NULL;
	home_dir = find_env(env, "HOME=");
	getcwd(cur_dir, MAX_SIZE_PATH);//!need to defense
	if (argv[2])
	{
		PRINT_ERROR_AND_RET(argv[0], STR_NOT_IN_PWD, argv[1]);
	}
	else if (!argv[1] || ft_strequ(argv[1], "~") || ft_strequ(argv[1], "--"))
	{
		chdir(home_dir);//!need to defense
		my_setenv("PWD", home_dir, cur_dir);
	}
	else
	{
		if (ft_strstr(argv[1], "~/"))
			full_path = ft_strjoin(home_dir, argv[1] + 1);//!need to defense
		if (check_dir_and_path_for_err(argv))//! move step again
			return (-1);
		if (check_dots_and_hyphen(argv, cur_dir, env))
		{
			chdir(!full_path ? argv[1] : full_path);//!need to defense
			my_setenv("PWD", argv[1], cur_dir);
		}
	}
	ft_strdel(&home_dir);
	ft_strdel(&full_path);
	return (0);
}
