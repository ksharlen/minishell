/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rloraine <rloraine@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/26 23:29:11 by rloraine          #+#    #+#             */
/*   Updated: 2019/09/26 23:40:05 by rloraine         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		echo(char *const argv[])
{
	int n;

	n = 1;
	if (ft_strequ(argv[n], "-n"))
	{
		if (argv[++n])
			while (argv[n])
				ft_printf("%s", argv[n++]);
		return (0);
	}
	else
		if (argv[n])
			while (argv[n])
				ft_printf("%s", argv[n++]);
	ft_printf("\n");
	return (0);
}
