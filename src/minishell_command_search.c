/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_command_search.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 14:50:39 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 20:02:32 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	find_from_interlnal_dir_ex(const char *cmd)
{
	char	**p_internal_cmd;

	p_internal_cmd = g_internal_commands;
	while (*p_internal_cmd)
	{
		if (!ft_strcmp(*p_internal_cmd, cmd))
			return (FOUND_INTERNAL_DIR);
		++p_internal_cmd;
	}
	return (NOT_FOUND);
}

int		minishell_command_search(const char *cmd, char *path_ex)
{
	ft_bzero(path_ex, MAX_SIZE_PATH + 1);
	if (cmd && path_ex && *cmd)
	{
		if (find_from_interlnal_dir_ex(cmd) == FOUND_INTERNAL_DIR)
		{
			ft_strcpy(path_ex, INTERNAL_PATH_CMD);
			ft_strcat(path_ex, cmd);
			return (FOUND_INTERNAL_DIR);
		}
		else if (find_in_the_var_path_env(getenv("PATH"), cmd, path_ex) == FOUND_PATH_ENV)
			return (FOUND_PATH_ENV);
		// else if (find_from_path_env(cmd) == FOUND)
		// 	ft_strcpy(path_ex, )
	}
	//сначала ищем в нашем каталоге
	//потом ищем в каталогах PATH
	//Если не нашли нигде, возвращаем -1.
	return (NOT_FOUND);
}
