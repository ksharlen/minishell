/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:28 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/14 18:45:55 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

struct s_nameval	split_name_val(const char *nameval)
{
	struct s_nameval	nval;
	size_t				len_name;

	nval.name = NULL;
	nval.value = NULL;
	if (nameval && *nameval)
	{
		len_name = ft_strnlen(nameval, '=');
		nval.name = ft_strsub(nameval, 0, len_name);
		nval.value = ft_strtabdup(nameval + len_name + 1);
	}
	return (nval);
}

static void			push_env(t_env *env, char *const argv[])
{
	size_t		len_argv;
	char *const	*p_argv;
	char		**p_cmd_argv;

	len_argv = ft_lineslen(argv);
	p_argv = argv;
	env->cmd_argv = (char **)ft_memalloc(sizeof(char *) * (len_argv + 1));
	p_cmd_argv = env->cmd_argv;
	while (*p_argv)
	{
		*p_cmd_argv = ft_strdup(*p_argv);
		++p_argv;
		++p_cmd_argv;
	}
}

static void			env_del(void)
{
	ft_strdel_split(environ);
	free(environ);
	environ = NULL;
}

int					work_cmd(char *const argv[], t_env *env)
{
	enum e_find	search;

	search = NOT_FOUND;
	if (argv)
	{
		env->cmd = *argv;
		if (!env->cmd)
		{
			ft_print_lines(environ);
			return (search);
		}
		push_env(env, argv);
		search = exec_env(env);
		ft_strdel_split(env->cmd_argv);
		free(env->cmd_argv);
		env->cmd_argv = NULL;
	}
	if (env->opt & F_I)
		env_del();
	return (search);
}

void				work_opt(char *const *p_argv, t_env *env)
{
	char	**copy_environ;

	copy_environ = environ;
	if (*p_argv && !ft_strcmp(*p_argv, "-i"))
	{
		environ = (char **)ft_memalloc(sizeof(char *));
		environ[0] = NULL;
		++p_argv;
	}
	if (p_argv && *p_argv && !ft_strcmp(*p_argv, "-P"))
	{
		++p_argv;
		env->path_exec = *p_argv;
		env->opt |= F_P;
		if (*p_argv)
			p_argv++;
	}
	if (p_argv && *p_argv)
		p_argv = change_value_name(p_argv);
	if (p_argv && *p_argv && !ft_strcmp(*p_argv, "-u"))
		p_argv = u_flag(++p_argv);
	work_cmd(p_argv, env);
	environ = copy_environ;
}
