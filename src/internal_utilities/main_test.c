/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:29:05 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 19:12:54 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		main(void)
{
	int ret_setenv;

	ret_setenv = minishell_unsetenv("LESS");
	if (ret_setenv == SUCCESS)
		ft_printf("========SUCCESS=========\n");
	else if (ret_setenv == FAILURE)
		ft_printf("========FAILURE=========\n");
	ft_printf("len_env[2] = %d\n", environ[0][2]);
	// ft_print_lines(environ);
	return (0);
}