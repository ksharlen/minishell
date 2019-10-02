/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_greeting.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/23 20:12:47 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/02 18:58:53 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		get_curr_time(char *curr_time)
{
	time_t	date;
	char	*str_date;

	ft_bzero(curr_time, SIZE_TIME + 1);
	time(&date);
	str_date = ctime(&date);
	ft_memcpy(curr_time, str_date + TO_TIME, SIZE_TIME);
}

static void		get_uname(char *uname)
{
	uid_t	uid;
	char	*pw_name;

	uid = getuid();
	pw_name = getpwuid(uid)->pw_name;
	ft_bzero(uname, MAX_UNAME);
	ft_strcat(uname, pw_name);
}

static char		*get_curr_dir(char *curr_dir, const char *home_dir)
{
	char	*p_str;

	ft_bzero(curr_dir, MAX_SIZE_PATH);
	getcwd(curr_dir, MAX_SIZE_PATH);
	if (!ft_strcmp(home_dir, curr_dir))
		return ("~/");
	else if (*(curr_dir) && *(curr_dir + 1))
	{
		p_str = ft_strrchr(curr_dir, '/');
		p_str++;
	}
	else
		p_str = curr_dir;
	return (p_str);
}

void			minishell_greeting(const char *home_dir)
{
	struct s_entry	entry;
	char			*curr_dir_without_full_path;

	get_curr_time(entry.time);
	get_uname(entry.uname);
	curr_dir_without_full_path = get_curr_dir(entry.curr_dir, home_dir);
	ft_printf("[%s] %s%s%s %s%s%s $>", entry.time, COLOR_UNAME, entry.uname,
		COLOR_DEFAULT, COLOR_DIR, curr_dir_without_full_path, COLOR_DEFAULT);
}
