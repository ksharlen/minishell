/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:35:31 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/04 20:13:49 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to rename and push into libft */

static char	*find_env(char *env[], char *key)
{
	char	*tmp;
	int		n;

	n = -1;
	while (env[++n])
		if (ft_strstr(env[n], key))
			tmp = ft_strdup(ft_strchr(env[n], '/'));//!need to defense
	return (tmp);
}

static void	back_step(char *cur_dir, char **full_path)
{
	char	*new_dir;
	int		i;
	int		new_len;

	i = -1;
	new_len = 0;
	while (cur_dir[new_len])
		++new_len;
	while (cur_dir[new_len] != '/')
		--new_len;
	new_dir = ft_strsub(cur_dir, 0, new_len);//!need to defense
	new_dir[i] = '\0';
	(*full_path) = new_dir;
	ft_strdel(&new_dir);
}

static int	check_access(char *argv[], char **check_path)
{
	if (!(access(check_path, F_OK)))
	{
		if (access(check_path, W_OK))
		{
			ft_strdel(check_path);
			PRINT_ERROR_AND_RET(argv[0], PERM_DENIED, argv[1]);
		}
		ft_strdel(check_path);
		return (0);
	}
	ft_strdel(check_path);
	PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, argv[1]);
}

static int	valid(char *argv[], char *home_dir)
{
	int		i;
	int		check;
	char	*check_path;

	i = -1;
	check = 0;
	if (!argv)
		return (0);
	if (!ft_strstr(argv[1], home_dir))
		check_path = ft_strjoin(home_dir, argv[1] + 1);//!need to defense
	else
		check_path = ft_strdup(argv[1]);//!need to defense
	while (argv[1][++i] && ++check)
	{
		if (i == MAX_SIZE_PATH)
			PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, argv[1]);
		if (argv[1][i] == '/')
			if (check > MAX_UNAME)
				PRINT_ERROR_AND_RET(argv[0], FILE_TO_LONG, argv[1]);
	}
	if (!(check_access(argv, &check_path)))
		return (0);
	PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, argv[1]);
}

static int	check_first_arg(char *argv[], char *env[], char *home_dir,\
char **full_path)
{
	char	*tmp;
	char	cur_dir[MAX_SIZE_PATH + 1];

	tmp = find_env(env, "OLDPWD=");//!need to defense
	getcwd(cur_dir, MAX_SIZE_PATH);//!need to defense
	if (!argv[1] || ft_strequ(argv[1], "~") || ft_strequ(argv[1], "--"))
		(*full_path) = home_dir;
	else if (ft_strstr(argv[1], "~/"))
		(*full_path) = ft_strjoin(home_dir, argv[1] + 1);//!need to defense
	else if (ft_strequ(argv[1], "."))
		my_setenv("OLDPWD", cur_dir, NULL);
	else if (ft_strequ(argv[1], ".."))
		back_step(cur_dir, full_path);
	else if (ft_strequ(argv[1], "-"))
		(*full_path) = tmp;
	else
	{
		(*full_path) = argv[1];
		if (valid(argv, home_dir))
			return (-1);
	}
	ft_strdel(&tmp);
	return (0);
}

int			cd(int argc, char *argv[], char *env[])
{
	char	cur_dir[MAX_SIZE_PATH + 1];
	char	*home_dir;
	char	*full_path;

	P_UNUSED(argc);
	full_path = NULL;
	home_dir = find_env(env, "HOME=");//!need to defense
	getcwd(cur_dir, MAX_SIZE_PATH);
	if (argv[2])
	{
		PRINT_ERROR_AND_RET(argv[0], STR_NOT_IN_PWD, argv[1]);
	}
	else
	{
		if (check_first_arg(argv, env, home_dir, &full_path))
			return (-1);
		chdir(full_path);//!need to defense
		my_setenv("PWD", full_path, cur_dir);
	}
	ft_strdel(&home_dir);
	return (0);
}
