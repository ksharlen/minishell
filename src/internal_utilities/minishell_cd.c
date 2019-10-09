/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:44:40 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/09 17:13:03 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static int	goto_path(const char *path)
{
	P_UNUSED(path);
	return (SUCCESS);
}

static int	valid_path(const char *path)
{
	size_t		len_filename;
	size_t		len_full_path;
	const char	*p_path;

	p_path = path;
	len_full_path = 0;
	while (*p_path)
	{
		if (*p_path == '/')
			++p_path;
		len_filename = ft_strnlen(p_path, '/');
		if (len_filename > MAX_UNAME)
		{
			CD_ERR(N_TOO_LONG, EMPTY_STR);
			return (FAILURE);
		}
		len_full_path += len_filename;
		p_path += len_filename;
	}
	if (len_full_path > MAX_SIZE_PATH)
	{
		CD_ERR(N_TOO_LONG, EMPTY_STR);
		return (FAILURE);
	}
	return (SUCCESS);
}

static int	work_cd(const char *path)
{
	enum e_u_err	err;

	err = FAILURE;
	if (*path)
	{
		err = valid_path(path);
		if (err != FAILURE)
			err = goto_path(path);
	}
	return (err);
}

int			minishell_cd(int argc, char **argv, char **env)
{
	P_UNUSED(env);
	if (argv[0] && argc > 0)
	{
		if (argc == 1)//Сделать проверку на спец символы (~/ / и тд.)
		{
			//!вызов ф-ии с переходом в home_dir
		}
		else if (argc > 2)
			CD_ERR(CD_TOO_MANY, EMPTY_STR);
		else
		{
			work_cd(PATH);
		}
		//меняем pwd
	}
	return (0);
}

// dfdfdfdfdfdfsdafasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfsdfasdfasdfasdfasdfasdfasdfasdfasdfasdfasdfsdfasdfasdfasdfasdfasdfasdfsadfasdfasdfasdfsadfasdfasdfasdfasfsdfasdfasdfasfsdfasfsdfasdfasdfasdfsadfasdfasdfasdfasfsdfasdfasdfsadfsadfsdfsdfsdafasdfddf