/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/03 20:03:21 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/03 21:13:38 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "curses_tests.h"

static void		push_prev_buf(char *prev, char *curr)
{
	bzero(prev, SIZE_BUF);
	strcpy(prev, curr);
}

static int		sys_key(int key)
{
	if (key == 3)
	{
		return (1);
		//
	}
	else if (key == 12)
	{
		clear();
		PRINT_U();
		return (1);
	}
	else if (key == 28)
		exit(EXIT_SUCCESS);
	return (0);
}

static int		parse_key(int key, char *buf)
{
	if (sys_key(key))
		;
	else
	{
		if (key == '\n')
		{
			refresh();
			return (-1);
		}
	}
	return (0);
}

static int		get_string(char *curr)
{
	int key;
	int ret_parse_key;

	PRINT_U();
	while (TRUE)
	{
		key = getch();
		ret_parse_key = parse_key(key, curr);
		if (key > -1 && key < 128 && !CHECK_COMBO_KEY(key))
			strcat(curr, (char *)&key);
		if (ret_parse_key == -1)
		{
			PRINT_U();
			printw("%s\n", curr);
			return (-1);
		}
	}
	return (0);
}

static char	*read_stdio(void)
{
	char	curr[SIZE_BUF];
	char	prev[SIZE_BUF];
	char	*read_str;

	bzero(curr, SIZE_BUF);
	get_string(curr);
	read_str = strdup(curr);
	if (!strcmp(curr, "exit"))
		exit(EXIT_SUCCESS);
	push_prev_buf(prev, curr);
	return (read_str);
}

static void exec_ve(const char *cmd)
{
	pid_t pid;
	int		status_child;
	char *argv[] = { "-la", NULL };
	char path_cmd[1000] = {0};

	strcat(path_cmd, PATH);
	strcat(path_cmd, cmd);
	printw("path_cmd: %s\n", path_cmd);
	pid = fork();
	if (!pid)
	{
		execve(path_cmd, argv, NULL);
		exit(EXIT_SUCCESS);
	}
	else
		wait(&status_child);
}

int		main(void)
{
	WINDOW *win_ptr;
	char *need_parse;
	t_argv	*elem;

	win_ptr = initscr();
	raw();
	while (TRUE)
	{
		need_parse = read_stdio();
		exec_ve(need_parse);
	}
	endwin();
	return (0);
}