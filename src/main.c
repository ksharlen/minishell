/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:09:46 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 16:12:20 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_internal_commands[] = {
	"0cd",
	"1echo",
	"2env",
	"3setenv",
	"4unsetenv",
	"5exit"
};

int		main(int argc, char **argv, char **env)
{
	char	*str_stdio;
	t_argv	*beg;

	P_UNUSED(argc);
	P_UNUSED(argv);
	system("clear");
	while (1)
	{
		minishell_greeting(getenv("HOME"));
		str_stdio = minishell_read_stdio();
		beg = minishell_parse_str(str_stdio);
		minishell_command_execution(beg, env);
		garbage_collector_internal(&beg);
	}
	return (0);
}
