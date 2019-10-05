/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:29:05 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 18:39:24 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		main(void)
{
	int ret_setenv;

	ret_setenv = minishell_unsetenv("LESS");
	if (ret_setenv == SUCCESS)
		ft_printf("\e[32;1m========SUCCESS=========\n");
	else if (ret_setenv == FAILURE)
		ft_printf("\e[31;1m========FAILURE=========\n");
	ft_print_lines(environ);
	return (0);
}