/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 22:35:31 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/01 20:13:45 by rloraine         ###   ########.fr       */
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
	while (env[++n])
		if (ft_strstr(env[n], "OLDPWD"))
			tmp = ft_strdup(ft_strchr(env[n], '/'));
	if (ft_strequ(argv[1], "."))
		return (0);
	else if (ft_strequ(argv[1], ".."))
	{
		get_new_path(cur_dir);
		return (0);
	}
	else if (ft_strequ(argv[1], "-"))
	{
		chdir(tmp);
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
	while (argv[1][++i])
	{
		if (i == MAX_SIZE_PATH)
		{
			PRINT_ERROR(argv[0], "no such file or directory:", argv[1]);
			return (-1);
		}
		if (argv[1][i] == '/')
		{
			if (check > 255)
			{
				PRINT_ERROR(argv[0], FILE_TO_LONG, argv[1]);
				return (-1);
			}
		}
		++check;
	}
	if (!access(argv[0], F_OK))
	{
		if (!access(argv[0], W_OK))
			return (0);
		else
		{
			PRINT_ERROR(argv[0], "premission denied:", argv[1]);
			return (-1);
		}		
	}
	else
	{
		PRINT_ERROR(argv[0], "no such file or directory:", argv[1]);
		return (-1);
	}
	return (0);
}

int			cd(char *const argv[], char *const env[])
{
	char	cur_dir[MAX_SIZE_PATH + 1];
	char	*home_dir;
	char	*full_path;
	int		n;

	n = -1;
	full_path = NULL;
	while (env[++n])
		if (ft_strstr(env[n], "HOME="))
			home_dir = ft_strdup(ft_strchr(env[n], '/'));
	if (!(getcwd(cur_dir, MAX_SIZE_PATH)))
		error();
	if (!argv[1] || ft_strequ(argv[1], "~") || ft_strequ(argv[1], "--"))
	{
		if (chdir(home_dir))
			exit(0);
		my_setenv("PWD", home_dir, cur_dir);
	}
	else if (argv[2])
	{
		PRINT_ERROR(argv[0], "string not in pwd:", argv[1]);
		return (-1);
	}
	else
	{
		if (ft_strstr(argv[1], "~/"))
			full_path = ft_strjoin(home_dir, argv[1]);
		if (check_dir_and_path_for_err(argv))
			return (-1);
		if (check_dots_and_hyphen(argv, cur_dir, env))
		{
			if (chdir(!full_path ? argv[1] : full_path))
			{
				PRINT_ERROR(argv[0], "no such file or directory:", argv[1]);
				return (-1);
			}
			my_setenv("PWD", argv[1], cur_dir);
		}
	}
	free(home_dir);
	return (0);
}
