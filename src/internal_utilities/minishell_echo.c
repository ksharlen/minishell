/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_echo.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/08 20:25:02 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/08 20:49:36 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

// static int	get_opt(int argc, char *const argv[])
// {
// 	int	ch;

// 	ch = 0;
// 	if (argv)
// 	{
// 		while ((ch = getopt(argc, argv, ECHO_OPT)) != -1)
// 			;
// 	}
// 	return (SUCCESS);
// }

void		work_echo(char *const argv[], unsigned char *flag)
{
	while (*argv && *(argv + 1))
	{
		ft_printf("%s ", *argv);
		++argv;
	}
	ft_printf("%s", *argv);
	*flag == FLAG_ON ? ft_printf("%%\n") : ft_printf("\n");
	// if (*flag == FLAG_OFF)
	// 	ft_printf("\n");
	// else
	// 	ft_printf("%%\n");
}

int			minishell_echo(int argc, char **argv, char **env)
{
	unsigned char flag;
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
		work_echo(argv, &flag);
	}
	return (0);
}