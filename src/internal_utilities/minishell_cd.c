/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_cd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 15:44:40 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/10 21:45:15 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static int	check_file(const char *path)
{
	struct stat		st;
	enum e_u_err	err;

	err = FAILURE;
	stat(path, &st);
	if (st.st_mode & S_IFDIR)
		err = SUCCESS;
	else
		CD_ERR(NOT_DIR, path);
	return (err);
}

static int	goto_path(const char *path)
{
	int				ret_chdir;
	enum e_u_err	err;

	err = FAILURE;
	ret_chdir = access(path, F_OK);
	if (ret_chdir == FAILURE)
		CD_ERR(S_NO_SUCH, path);
	else
	{
		if (check_file(path) == FAILURE)
			return (FAILURE);
		ret_chdir = access(path, X_OK);
		if (ret_chdir == FAILURE)
			CD_ERR(PERM, path);
		else
		{
			ret_chdir = chdir(path);
			if (ret_chdir == FAILURE)
				CD_ERR(NOT_DIR, path);
			else
				err = SUCCESS;
		}
	}
	return (err);
}

static int	valid_path(const char *path)
{
	size_t		len_filename;
	size_t		len_full_path;
	const char	*p_path;

	p_path = path;
	len_full_path = 0;
	while (p_path && *p_path)
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
	char			*buf_path;

	err = FAILURE;
	if (path)
	{
		err = valid_path(path);
		if (err != FAILURE)
		{
			if (*path == '~' || !(*path) || !ft_strcmp(path, "--"))
			{
				buf_path = (char[MAX_SIZE_PATH + 1]){0};
				work_home_dir(path, buf_path);
				err = goto_path(buf_path);
			}
			else if (!ft_strcmp(path, "-"))
				err = goto_path(getenv("OLDPWD"));
			else
				err = goto_path(path);
		}
	}
	return (err);
}

int			minishell_cd(int argc, char **argv, char **env)
{
	enum e_u_err	err;
	char			*cwd;

	P_UNUSED(env);
	err = FAILURE;
	if (argv[0] && argc > 0)
	{
		if (argc == 1)
			err = work_cd("");
		else if (argc > 2)
			CD_ERR(CD_TOO_MANY, EMPTY_STR);
		else
			err = work_cd(PATH);
		if (err == SUCCESS)
		{
			cwd = (char[MAX_SIZE_PATH + 1]){0};
			getcwd(cwd, MAX_SIZE_PATH);
			minishell_setenv("OLDPWD", getenv("PWD"), FLAG_ON);
			minishell_setenv("PWD", cwd, FLAG_ON);
		}
	}
	return (0);
}
