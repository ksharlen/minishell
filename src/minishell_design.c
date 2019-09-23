/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_design.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:12:47 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/23 21:17:35 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//!	[time] uname dir $>

#include "minishell.h"

static void		get_curr_time(char *curr_time)
{
	time_t	date;
	char 	*str_date;

	time(&date);
	str_date = ctime(&date);
	ft_bzero(curr_time, SIZE_TIME + 1);
	ft_memcpy(curr_time, str_date + TO_TIME, SIZE_TIME);
}

static void		get_uname(char *uname)
{
	uid_t			uid;
	char			*pw_name;

	uid = getuid();
	pw_name = getpwuid(uid)->pw_name;
	bzero(uname, MAX_UNAME);
	ft_strcat(uname, pw_name);
}

static void		get_curr_dir(char *curr_dir)
{
	size_t		tmp_len;
	char		*p_str;

	ft_bzero(curr_dir, MAX_SIZE_PATH);
	getcwd(curr_dir, MAX_SIZE_PATH);
	p_str = ft_strmoveptr_end(curr_dir, 0);
	p_str = ft_strrchr(curr_dir, '/');
	++p_str;
	tmp_len = ft_strlen(p_str); //!ОТСЮДА БЕДА
	//ft_printf("tmp_len: %ld\n", tmp_len);
	ft_strcpy(curr_dir, p_str);
	curr_dir[tmp_len] = 0;
	// // while (p_str && *p_str && (*p_str != '/'))
	// // 	--p_str
}

void			minishell_design(void)
{
	struct s_entry entry;

	get_curr_time(entry.time);
	get_uname(entry.uname);
	get_curr_dir(entry.curr_dir);
	ft_printf("[%s] %s {/green}%s{/white} $>", entry.time, entry.uname, entry.curr_dir);
	//время
	//имя пользователя
	//текущая дерикторя
	//ft_printf("[%s] %s %s $>", );
}