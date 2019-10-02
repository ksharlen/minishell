/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 16:09:46 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/02 18:40:39 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_internal_commands[] = {
	"0cd",
	"1echo",
	"2env",
	"3pwd"
	// "3setenv",
	// "4unsetenv",
	// "5pwd"
	// "5exit",
};

static void tmp1(int sig)
{
	if (sig == SIGINT)
		return ;
}

int		main(int argc, char **argv, char **env)
{
	char				*str_stdio;
	t_argv				*beg;
	struct s_key_data	key_minishell_history;
	enum e_find			search;

	signal(SIGINT, tmp1);
	P_UNUSED(argc);
	P_UNUSED(argv);
	search = NOT_FOUND;
	minishell_history_init(&key_minishell_history);
	system("clear");
	while (INF)
	{
		minishell_greeting(getenv("HOME"));
		str_stdio = minishell_read_stdio();
		minishell_push_minishell_history(str_stdio, &key_minishell_history);
		beg = minishell_parse_str(str_stdio);
		search = minishell_command_execution(beg, env);
		garbage_collector_internal(&beg);
		if (search == FOUND_EXIT)
			break ;
	}
	minishell_history_close(&key_minishell_history);
	return (0);
}
