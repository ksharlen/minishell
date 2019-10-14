/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_geters.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/13 18:45:38 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/14 16:55:55 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		mshell_gethome_env(char *buf)
{
	char	*path_env;

	path_env = NULL;
	if (buf)
	{
		path_env = minishell_getenv("PATH");
		if (!path_env)
			ft_strcpy(buf, DFLT_PATH_ENV);
		else
			ft_strcpy(buf, path_env);
		return (SUCCESS);
	}
	return (FAILURE);
}

int		mshell_getpwd(char *buf)
{
	if (getcwd(buf, MAX_SIZE_PATH))
		return (SUCCESS);
	else
		return (FAILURE);
}

int		mshell_getoldpwd(char *buf)
{
	char	*oldpwd;

	if (buf)
	{
		if ((oldpwd = minishell_getenv("OLDPWD")))
		{
			ft_strcpy(buf, oldpwd);
			return (SUCCESS);
		}
	}
	return (FAILURE);
}

int		mshell_gethomedir(char *buf)
{
	uid_t			uid;
	char			*home_dir;

	if (buf)
	{
		if ((home_dir = minishell_getenv("HOME")))
			ft_strcpy(buf, home_dir);
		else
		{
			uid = getuid();
			ft_strcpy(buf, getpwuid(uid)->pw_dir);
		}
		return (SUCCESS);
	}
	return (FAILURE);
}
