/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/07 20:43:41 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static void		env_init(t_env *env)
{
	env->cmd = NULL;
	env->opt = 0;
}

static void		get_opt(int argc, char **opts, t_env *env)
{
	int ch;

	while ((ch = getopt(argc, opts, ENV_OPT)) != -1)
	{
		if (ch == 'P')
			env->opt |= F_P;
		else if (ch == 'S')
			env->opt |= F_S;
		else if (ch == 'i')
			env->opt |= F_I;
		else if (ch == 'u')
			env->opt |= F_U;
		else if (ch == '?')
		{
			ft_printf("%s\n	   %s\n", USG, USG_1);
			exit(EXIT_FAILURE);
		}
	}
}

static char	*const *skip_opt(char *const argv[])
{
	char *const *p_argv;

	p_argv = argv;
	while (*p_argv)
	{
		if (!ft_strcmp(*p_argv, "-i"))
			++p_argv;
		else
			break ;
	}
	return (p_argv);
}

static int	work_env(const int argc, char **argv, t_env *env)
{
	char *const *p_argv;

	P_UNUSED(argc);
	p_argv = skip_opt(argv + 1);
	if (!p_argv)
	{
		ft_printf("%s\n	   %s\n", USG, USG_1);
		exit(EXIT_FAILURE);
	}
	work_opt(p_argv, env);
	return (SUCCESS);
}

int		minishell_env(int argc, char **argv, char **env)
{
	t_env			m_env;
	enum e_u_err	err;
	P_UNUSED(argc);
	P_UNUSED(argv);
	P_UNUSED(env);

	err = FAILURE;
	env_init(&m_env);
	if (argc == 1)
		ft_print_lines(environ);
	else
	{
		if (argv[1][0] == '-')
			get_opt(argc, argv, &m_env);
		err = work_env(argc, argv, &m_env);
	}
	return (SUCCESS);
}
