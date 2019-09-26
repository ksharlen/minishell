/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_read_stdio.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/24 15:06:22 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/26 19:39:25 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*minishell_read_stdio(void)
{
	char	*read_stdio;
	int		stat_gnl;

	stat_gnl = get_next_line(STDIN, &read_stdio, FLAG_OFF);
	if (!stat_gnl || stat_gnl == -1)
		return (NULL);
	return (read_stdio);
}
