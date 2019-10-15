/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pull_permission.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:56:31 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/17 15:31:20 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

static void	push_permission_u(mode_t st_mode, char *str)
{
	int permiss_exe;

	permiss_exe = PERMISS_UX(st_mode);
	*str++ = ((st_mode & U_R) ? 'r' : '-');
	*str++ = ((st_mode & U_W) ? 'w' : '-');
	if (permiss_exe < 0)
		*str = (st_mode & U_X ? 's' : 'S');
	else
		*str = (st_mode & U_X ? 'x' : '-');
}

static void	push_permission_g(mode_t st_mode, char *str)
{
	int permiss_exe;

	permiss_exe = PERMISS_GX(st_mode);
	*str++ = ((st_mode & G_R) ? 'r' : '-');
	*str++ = ((st_mode & G_W) ? 'w' : '-');
	if (permiss_exe < 0)
		*str = (st_mode & G_X ? 's' : 'S');
	else
		*str = (st_mode & G_X ? 'x' : '-');
}

static void	push_permission_o(mode_t st_mode, char *str)
{
	int permiss_exe;

	permiss_exe = PERMISS_OX(st_mode);
	*str++ = ((st_mode & O_R) ? 'r' : '-');
	*str++ = ((st_mode & O_W) ? 'w' : '-');
	if (permiss_exe < 0)
		*str = (st_mode & O_X ? 't' : 'T');
	else
		*str = (st_mode & O_X ? 'x' : '-');
}

char		*pull_access_permission(const mode_t st_mode)
{
	size_t			size_permission;
	char			*return_str;
	char			*p_run;

	size_permission = 9;
	return_str = (char *)ft_strnew(sizeof(char) * size_permission);
	p_run = return_str;
	push_permission_u(st_mode, p_run);
	p_run += 3;
	push_permission_g(st_mode, p_run);
	p_run += 3;
	push_permission_o(st_mode, p_run);
	return (return_str);
}
