/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_search_path_env.c                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 16:12:04 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/29 14:13:27 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		push_path(const char *cmd, const char *path, char *path_ex)
{
	ft_strcpy(path_ex, path);
	ft_strcat(path_ex, "/");
	ft_strcat(path_ex, cmd);
}

int			search_path(const char *path, const char *cmd, char *path_ex)
{
	DIR				*dir;
	struct dirent	*dent;
	enum e_find		search;

	search = NOT_FOUND;
	dir = opendir(path);
	while ((dent = readdir(dir)))
	{
		if (!ft_strcmp(dent->d_name, cmd))
		{
			push_path(cmd, path, path_ex);
			search = FOUND;
			break ;
		}
	}
	closedir(dir);
	return (search);
}

int				find_in_the_var_path_env(const char *path_env,
	const char *cmd, char *path_ex)
{
	char		**paths;
	char		**p_paths;
	enum e_find	search;

	ft_bzero(path_ex, MAX_UNAME + 1);
	paths = NULL;
	search = NOT_FOUND;
	if (path_env && cmd && path_ex && *path_env && *cmd)
	{
		paths = ft_strsplit_skip_space((char *)path_env, PATH_SPLIT);
		p_paths = paths;
		while (*p_paths)
		{
			if (search_path(*p_paths, cmd, path_ex) == FOUND)
			{
				search = FOUND_PATH_ENV;
				break ;
			}
			++p_paths;
		}
		ft_strdel_split(paths);
		strddel(&paths);
	}
	return (search);
}
