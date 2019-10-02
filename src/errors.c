/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 16:46:28 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/02 20:08:55 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

const char *const g_merrors[] = {
	"open_error",
	"close_error",
	"read_error",
	"opendir_error",
	"closedir_error",
	"readdir_error",
	"fork_error",
	"execve_error",
	"wait_error",
	"signal_error",
	"time_error",
	"ctime_error",
	"waitpid_error",
	"kill_error",
	"getcwd_error",
	"malloc_error",
	"chdir_error",
	"stat_error",
	"fstat_error",
	"lstat_error"
};

void	err_str(t_error merror, const char *add_text)
{
	if (add_text && *add_text)
		ft_printf("%s: %s\n", add_text, g_merrors[merror]);
	else
		ft_printf("%s\n", g_merrors[merror]);
}

void	err_exit(t_error merror, const char *add_text)
{
	err_str(merror, add_text);
	exit(EXIT_FAILURE);
}
