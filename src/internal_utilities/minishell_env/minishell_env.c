/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/14 15:18:51 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static size_t	len_opt(char *const argv[])
{
	size_t		len;

	len = 1;
	if (argv && *argv)
	{
		++argv;
		while (*argv && *argv[0] == '-')
		{
			++len;
			++argv;
		}
	}
	return (++len);
}

static void		env_init(t_env *env)
{
	env->cmd = NULL;
	env->opt = 0;
}

static int		get_opt(int argc, char **opts, t_env *env)
{
	int				ch;
	enum e_u_err	err;

	// printf("opts: %s\n", *opts);
	printf("opts[index]: %s\n", opts[optind]);
	ch = 0;
	err = SUCCESS;
	optind = 1;
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
			err = FAILURE;
			ft_printf("%v%s\n	   %s\n", STDERR_FILENO, USG, USG_1);
			return (err);
		}
	}
	return (err);
}

int				minishell_env(int argc, char **argv, char **env)
{
	t_env			m_env;
	size_t			l_opt;
	enum e_u_err	err;

	P_UNUSED(env);
	err = FAILURE;
	env_init(&m_env);
	if (argc == 1)
		ft_print_lines(environ);
	else
	{
		l_opt = len_opt(argv);
		err = get_opt(l_opt, argv, &m_env);
		if (err == SUCCESS)
		{
			++argv;
			work_opt(argv, &m_env);
		}
	}
	return (err);
}
