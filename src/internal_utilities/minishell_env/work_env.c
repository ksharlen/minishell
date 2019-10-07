/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:28 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/07 21:20:37 by ksharlen         ###   ########.fr       */
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
		nval.name = ft_strsub(nameval, 0, len_name = ft_strnlen(nameval, '='));
		nval.value = ft_strdup(nameval + len_name + 1);
	}
	//!Тут зафришить!!!!!!!!
	return (nval);
}

static void	push_env(t_env *env, char *const argv[])
{
	size_t	len_argv;
	char	*const *p_argv;
	char	**p_cmd_argv;

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

int		work_cmd(char *const argv[], t_env *env)
{
	char		path_ex[MAX_SIZE_PATH + 1];
	enum e_find	search;

	search = NOT_FOUND;
	if (argv)
	{
		env->cmd = *argv;
		push_env(env, argv);
		//!Зафришить
		search = (find_in_the_var_path_env(env->opt & F_P ? env->path_exec : getenv("PATH"), env->cmd, path_ex));
		if (search == NOT_FOUND)
			ENV_PRINT(S_NO_SUCH, env->cmd);
		else
			execute_cmd(env->cmd_argv, path_ex);
	}
	return (search);
}

void	work_opt(char *const *p_argv, t_env *env)
{
	char	**copy_environ;

	copy_environ = ft_linedup(environ);//?тут лежат наши переменные окружения для родителя
	if (env->opt & F_I)
		environ = NULL;//Подумать
	if (!ft_strcmp(*p_argv, "-P"))
	{
		++p_argv;
		env->path_exec = *p_argv++;
	}
	if (*p_argv)
		p_argv = change_value_name(p_argv);
	if (*p_argv && !ft_strcmp(*p_argv, "-u"))
		p_argv = u_flag(++p_argv); //?Переходим на следующий аргумент после флага u
	//!тут этап сборки программы с ее аргументами
	work_cmd(p_argv, env);
	environ = copy_environ;
}
