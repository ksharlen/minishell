/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:35:31 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/02 22:07:00 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* need to rename and push into libft */

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
	printf("%s\n", tmp);
	if (ft_strequ(argv[1], "."))
		return (0);
	else if (ft_strequ(argv[1], ".."))
	{
		get_new_path(cur_dir);
		return (0);
	}
	else if (ft_strequ(argv[1], "-"))
	{
		ft_printf("here\n");
		chdir(tmp);//!need to defense
		my_setenv("PWD", tmp, cur_dir);
		ft_printf("%s\n", tmp);
		free(tmp);
		return (0);
	}
	return (1);
}

int			check_dir_and_path_for_err(char *const argv[], char *path)
{
	int i;
	int check;

	i = -1;
	check = 0;
	printf("%s\n", path);
	while (path[++i] && ++check)
	{
		if (i == MAX_SIZE_PATH)
			PRINT_ERROR_AND_RET(argv[0], NO_SUCH_F_OR_D, path);
		if (argv[1][i] == '/')
		{
			if (check > 255)
				PRINT_ERROR_AND_RET(argv[0], FILE_TO_LONG, path);
		}
		printf("here\n");
	}
	if (!access(path, F_OK))
	{
		if (!access(argv[1], W_OK))
			return (0);
		else
			PRINT_ERROR_AND_RET(argv[0], PERM_DENIED, argv[1]);
	}
	return (-1);
}

static int	correct_cd_work(char *const argv[], char *const env[],\
char *cur_dir, char *full_path)
{
	// if (check_dir_and_path_for_err(argv, !full_path ? argv[1] : full_path))//! move step again
	// 	return (-1);
	if (check_dots_and_hyphen(argv, cur_dir, env))
	{
		chdir(!full_path ? argv[1] : full_path);//!need to defense
		my_setenv("PWD", argv[1], cur_dir);
	}
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
		correct_cd_work(argv, env, cur_dir, full_path);
	}
	ft_strdel(&home_dir);
	ft_strdel(&full_path);
	return (0);
}
