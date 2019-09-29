/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 23:29:11 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/29 17:10:41 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char *const argv[])
{
	int n;
	int flag;

	n = 1;
	flag = 0;
	if (ft_strequ(argv[n], "-n"))
		flag = 1;
	while (argv[n])
		ft_printf("%s ", argv[n++]);
	flag ? flag = 0 : ft_printf("\n");
	return (0);
}
