/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_init.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/05 11:54:26 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 12:36:20 by ksharlen         ###   ########.fr       */
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
	push_path(MRC, cwd, g_path.P_MSRC);
	push_path(MHISTORY, cwd, g_path.P_MSHIST);
	push_path(UTILITIES, cwd, g_path.P_INT_CMD);
}
