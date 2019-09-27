/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_push_minishell_history.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:31 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/27 18:01:21 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_key	getkey_internal(void)
{
	int 	fd;
	char 	*key;
	char	*num_str;
	int		key_int;

	fd = open(MRC, O_RDWR);
	get_next_line(fd, &key, FLAG_OFF);
	num_str = ft_stroneof(key, NUMBERS);
	key_int = ft_atoi(num_str);
	return (key_int);
}

static void		getdate_internal(char *date_ex_cmd)
{
	time_t		date_ex;
	char		*str_date;

	time(&date_ex);
	str_date = ctime(&date_ex);
	ft_strcpy(date_ex_cmd, str_date);
}

static void push_mhistory(struct s_minishell_history history_cmd)
{
	
}

void			minishell_push_minishell_history(const char *str_stdio, t_key *key)
{
	struct s_minishell_history	history_cmd;

	P_UNUSED(str_stdio);
	ft_bzero(history_cmd.date_ex_cmd, SIZE_DATE + 1);
	getdate_internal(history_cmd.date_ex_cmd);
	history_cmd.key = (*key);
	push_mhistory(history_cmd);
}
