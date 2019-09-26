/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/25 22:10:52 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 21:55:40 by ksharlen         ###   ########.fr       */
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

void	set_env(char *const argv[], char *const env[], char *cur_dir)
{
	char *pwd;

	P_UNUSED(env);
	pwd = ft_strjoin(cur_dir, argv[1]);
	setenv("OLDPWD", cur_dir, 1);
	setenv("PWD", pwd, 1);
}
