/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_tools.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/14 14:52:57 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/14 18:47:16 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		exec_env(const t_env *env)
{
	char		path_ex[MAX_SIZE_PATH + 1];
	t_argv		*new_cmd;
	enum e_find	search;

	search = NOT_FOUND;
	new_cmd = NULL;
	if (env)
	{
		if (env->opt & F_P)
		{
			search = search_path(env->path_exec, env->cmd, path_ex);
			if (search != NOT_FOUND)
				execute_cmd(env->cmd_argv, path_ex);
			else
				ENV_PRINT(ENV_NO_SUCH, env->cmd);
		}
		else
		{
			new_cmd = convert_structs(env);
			minishell_command_execution(new_cmd);
			free(new_cmd);
			new_cmd = NULL;
		}
	}
	return (search);
}

t_argv	*convert_structs(const t_env *conv_from)
{
	t_argv	*new;

	new = NULL;
	if (conv_from)
	{
		new = (t_argv *)ft_memalloc(sizeof(t_argv));
		if (!new)
			err_exit(E_MALLOC, "minishell");
		new->argv = conv_from->cmd_argv;
		new->argc = ft_lineslen(new->argv);
		new->next = NULL;
	}
	return (new);
}
