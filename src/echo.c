/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 23:29:11 by rloraine          #+#    #+#             */
/*   Updated: 2019/10/01 23:42:16 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(int argc, char *argv[], char *env[])
{
	int n;
	int flag;

	P_UNUSED(argc);
	P_UNUSED(env);
	n = 1;
	flag = 0;
	if (ft_strequ(argv[n], "-n"))
		flag = 1;
	while (argv[n])
		ft_printf("%s ", argv[n++]);
	flag ? flag = 0 : ft_printf("\n");
	return (0);
}
