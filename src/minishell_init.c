/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:54:26 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/09 23:14:26 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	minishell_paths_init(void)
{
	char cwd[MAX_SIZE_PATH + 1];

	ft_bzero(cwd, MAX_SIZE_PATH + 1);
	ft_bzero(g_path.P_INT_CMD, MAX_SIZE_PATH + 1);
	ft_bzero(g_path.P_MSRC, MAX_SIZE_PATH + 1);
	ft_bzero(g_path.P_MSHIST, MAX_SIZE_PATH + 1);
	getcwd(cwd, MAX_SIZE_PATH);
	minishell_setenv("SHELL", cwd, FLAG_ON);
	push_path(MRC, cwd, g_path.P_MSRC);
	push_path(MHISTORY, cwd, g_path.P_MSHIST);
	push_path(UTILITIES, cwd, g_path.P_INT_CMD);
	minishell_setenv("PWD", cwd, FLAG_OFF);
	minishell_setenv("OLDPWD", cwd, FLAG_OFF);
}
