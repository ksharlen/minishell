/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:28 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/07 16:57:21 by ksharlen         ###   ########.fr       */
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

int		work_cmd(char *const argv[], t_env *env)
{
	char		path_ex[MAX_SIZE_PATH + 1];
	enum e_find	search;

	search = NOT_FOUND;
	if (argv)
	{
		env->cmd = *argv++;
		env->cmd_argv = argv;
		search = (find_in_the_var_path_env(env->opt & F_P ? env->path_exec : getenv("PATH"), env->cmd, path_ex));
		if (search == NOT_FOUND)
			NO_SUCH(env->cmd);
		else
		{
			ft_printf("path_ex: %s\n", path_ex);
			exit(EXIT_FAILURE);
		}
	}
	return (search);
}

void	work_opt(char *const *p_argv, t_env *env)
{
	char	**copy_environ;
	char	**p_split;

	copy_environ = ft_linedup(environ);//?тут лежат наши переменные окружения для родителя
	if (env->opt & F_I)
		environ = NULL;//Подумать
	if (env->opt & F_P)
	{
		env->path_exec = *p_argv;
		++p_argv;
	}
	if (*p_argv)
		p_argv = change_value_name(p_argv);
	if (*p_argv && !ft_strcmp(*p_argv, "-u"))
		p_argv = u_flag(++p_argv); //?Переходим на следующий аргумент после флага u
	//!тут этап сборки программы с ее аргументами
	work_cmd(p_argv, env);

}
