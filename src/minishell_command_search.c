/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_search.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:50:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/29 14:13:44 by rloraine         ###   ########.fr       */
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
		if (!ft_strcmp(*p_internal_cmd, cmd))
			return (FOUND_OUR_DIR);
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
		if (find_from_interlnal_dir_ex(cmd) == FOUND_OUR_DIR)
		{
			ft_strcpy(path_ex, INTERNAL_PATH_CMD);
			ft_strcat(path_ex, cmd);
			search = FOUND_OUR_DIR;
		}
		else if (find_in_the_var_path_env(getenv("PATH"),
		cmd, path_ex) == FOUND_PATH_ENV)
			search = FOUND_PATH_ENV;
	}
	return (search);
}
