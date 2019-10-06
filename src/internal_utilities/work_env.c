/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_env.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 22:16:28 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/07 00:54:11 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

char	**split_s_key(const char *str)
{
	char **split;

	split = NULL;
	if (str)
		split = ft_strsplit_skip_space((char *)str, ' ');
	return (split);
}

static struct s_nameval	split_name_val(const char *nameval)
{
	struct s_nameval	nval;
	size_t				len_name;

	nval.name = NULL;
	nval.value = NULL;
	if (nameval && *nameval)
	{
		nval.name = ft_strsub(nameval, 0, len_name = ft_strnlen(nameval, '='));
		nval.value = ft_strdup(nameval + len_name + 1);
		ft_printf("name: %s\nval: %s\n", nval.name, nval.value);
	}
	return (nval);
}

static void		change_value_name(char **need_add)
{
	struct s_nameval nval;

	if (need_add && *need_add)
	{
		while (*need_add)
		{
			nval = split_name_val(*need_add);
			//!Зафришить!!!!!!!!!!!!!!!!!!!
			minishell_setenv(nval.name, nval.value, FLAG_ON);
			++need_add;
		}
	}
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
	if (*p_argv && !ft_strcmp(*p_argv, "-u") && !(env->opt & F_I))
	{
		if (*(++p_argv) && !ft_strcmp(*p_argv, "-S"))
			p_argv = u_flag(++p_argv);
			// //!Зафришить
		else
			minishell_unsetenv(*p_argv++);
	}
	if (*p_argv && !ft_strcmp(*p_argv, "-S"))
	{
		++p_argv;
		p_split = split_s_key(*p_argv);
		change_value_name(p_split);
	}
	else if (*p_argv)
		change_value_name((char **)*&p_argv);
}
