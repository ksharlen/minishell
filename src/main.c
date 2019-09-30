/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:09:46 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/30 17:57:51 by ksharlen         ###   ########.fr       */
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
	char				*str_stdio;
	t_argv				*beg;
	struct s_key_data	key_minishell_history;
	enum e_rw			rw;

	P_UNUSED(argc);
	P_UNUSED(argv);
	minishell_history_init(&key_minishell_history);
	system("clear");
	while (INF)
	{
		minishell_greeting(getenv("HOME"));
		str_stdio = minishell_read_stdio();
		minishell_push_minishell_history(str_stdio, &key_minishell_history);
		beg = minishell_parse_str(str_stdio);
		rw = minishell_command_execution(beg, env);
		garbage_collector_internal(&beg);
		if (rw == FOUND_EXIT);
			break ;
	}
	minishell_history_close(&key_minishell_history);
	return (0);
}
