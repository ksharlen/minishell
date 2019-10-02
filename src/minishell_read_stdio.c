/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_read_stdio.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/02 20:45:02 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell_read_stdio(void)
{
	char	*read_stdio;
	int		stat_gnl;

	if ((stat_gnl = get_next_line(STDIN, &read_stdio, FLAG_OFF)) == RET_ERROR)
		err_exit(E_MALLOC, "minishell");
	return (read_stdio);
}
