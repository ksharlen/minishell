/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_env.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/06 15:16:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/06 18:07:38 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "internal_utilities.h"

int		minishell_env(int argc, char **argv, char **env)
{
	P_UNUSED(argc);
	P_UNUSED(argv);
	P_UNUSED(env);
	if (argc == 1)
		ft_print_lines(environ);
	else
	{
		
	}
	return (SUCCESS);
}
