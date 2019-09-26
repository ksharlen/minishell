/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:10:52 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 21:36:40 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

#define MYERROR 1

// void	unset_env(char **argv, char **env)
// {
	
// }

void	my_setenv(char *key, char *value, char *old_pwd)
{
	if (ft_strequ(key, "PWD"))
	{
		setenv(key, value, 1);
		setenv("OLDPWD", old_pwd, 1);
	}
	else
	{
		//for env's keys
	}
}

void	set_env(t_argv *beg, char **env, char *cur_dir)
{
	char *pwd;

	pwd = ft_strjoin(cur_dir, beg->argv[1]);
	setenv("OLDPWD", cur_dir, 1);
	setenv("PWD", pwd, 1);
}
