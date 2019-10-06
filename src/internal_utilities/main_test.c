/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_test.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 16:29:05 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/06 23:34:47 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		main(int argc, char **argv, char **env)
{
	int 	err;
	size_t	len_env;

	// ret_setenv = minishell_unsetenv("XPC_");
	err = minishell_env(argc, argv, env);
	if (err == SUCCESS)
		ft_printf("\e[32;1m========SUCCESS=========\n");
	else if (err == FAILURE)
		ft_printf("\e[31;1m========FAILURE=========\n");
	// ft_printf("len_env[2] = %d\n", environ[0][2]);
	// len_env = ft_print_lines(environ);
	// ft_printf("len_env: %ld\n", len_env);
	return (0);
}
