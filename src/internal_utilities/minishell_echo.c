/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:25:02 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/08 21:59:31 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

static void	work_echo(char *const argv[])
{
	while (*argv && *(argv + 1))
	{
		ft_printf("%s ", *argv);
		++argv;
	}
	ft_printf("%s", *argv ? *argv : "");
}

int			minishell_echo(int argc, char **argv, char **env)
{
	unsigned char	flag;

	P_UNUSED(env);
	flag = FLAG_OFF;
	if (argc == 1)
		ft_putendl("");
	else
	{
		++argv;
		if (*argv && !ft_strcmp(*argv, "-n"))
		{
			++argv;
			flag = FLAG_ON;
		}
		work_echo(argv);
		if (argc > 2)
			flag == FLAG_ON ? ft_printf("\e[30;47m%%%s\n", COLOR_DEFAULT)
				: ft_printf("\n");
		else if (argc == 2 && flag == FLAG_OFF)
			ft_printf("\n");
	}
	return (0);
}
