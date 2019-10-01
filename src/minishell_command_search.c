/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_search.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:50:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/01 23:20:27 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_internal_cmd(const char *cmd, char *path_ex)
{
	enum e_find search_cmd;
	char **p_internal_cmd;

	search_cmd = NOT_FOUND;
	p_internal_cmd = g_internal_commands;
	while (*p_internal_cmd)
	{
		if (!ft_strcmp(cmd, "exit"))
			return (FOUND_EXIT);
		else if (!ft_strcmp(cmd, *(p_internal_cmd) + 1))
		{
			ft_strcpy(path_ex, *p_internal_cmd);
			search_cmd = FOUND_INTERNAL_CMD;
			break ;
		}
		++p_internal_cmd;
	}
	return (search_cmd);
}

int			minishell_command_search(const char *cmd, char *path_ex)
{
	enum e_find	search;

	search = NOT_FOUND;
	if (cmd && path_ex && *cmd)
	{
		ft_bzero(path_ex, MAX_UNAME + 1);
		if ((search = find_internal_cmd(cmd, path_ex)) == FOUND_EXIT)
			return (FOUND_EXIT);
		else if (search == FOUND_INTERNAL_CMD)
			return (search);
		else if (search_path(INTERNAL_DIR_CMD, cmd, path_ex) == FOUND)
			search = FOUND_SHELL_DIR;
		else if (find_in_the_var_path_env(getenv("PATH"),
		cmd, path_ex) == FOUND_PATH_ENV)
			search = FOUND_PATH_ENV;
	}
	return (search);
}
