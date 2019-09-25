/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:09:46 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/25 23:21:17 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		main(int argc, char **argv, char **env)
{
	char	*str_stdio;
	t_argv	*beg;

	P_UNUSED(argc);
	P_UNUSED(argv);
	system("clear");
	while (1)
	{
		minishell_greeting();
		str_stdio = minishell_read_stdio();
		beg = minishell_parse_str(str_stdio);
		minishell_command_execution(beg, env);
		garbage_collector_internal(&beg, &str_stdio);
	}
	return (0);
}
