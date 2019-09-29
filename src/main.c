/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:09:46 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 17:55:40 by ksharlen         ###   ########.fr       */
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
	t_key	key_minishell_history;

	P_UNUSED(argc);
	P_UNUSED(argv);
	key_minishell_history = getkey_internal();
	system("clear");
	while (1)
	{
		minishell_greeting(getenv("HOME"));
		str_stdio = minishell_read_stdio();
		minishell_push_minishell_history(str_stdio, &key_minishell_history);
		beg = minishell_parse_str(str_stdio);
		minishell_command_execution(beg, env);
		garbage_collector_internal(&beg);
	}
	return (0);
}
