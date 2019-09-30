/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_push_minishell_history.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:31 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/30 16:06:28 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void			getkey_internal(struct s_key_data *key)
{
	key->key_str = R_FVAL(MRC, KEY_LAST_CMD_MHISTORY);
	key->key = ft_atoi(key->key_str);
}

static void		getdate_internal(char *date_ex_cmd)
{
	time_t		date_ex;
	char		*str_date;

	time(&date_ex);
	str_date = ctime(&date_ex);
	ft_memcpy(date_ex_cmd, str_date, ft_strlen(str_date) - 1);
}

static void push_mhistory(struct s_key_data *k_data, const char *cmd_str)
{
	if (cmd_str && *cmd_str && k_data->fd_ms_history != -1)
		ft_printf("%v%d:[%s];%s\n", k_data->fd_ms_history, k_data->key, k_data->date_ex_cmd, cmd_str);
}

void			minishell_push_minishell_history(const char *str_stdio, struct s_key_data *k_data)
{
	if (str_stdio && k_data && *str_stdio && k_data->key_str)
	{
		ft_bzero(k_data->date_ex_cmd, SIZE_DATE + 1);
		getdate_internal(k_data->date_ex_cmd);
		push_mhistory(k_data, str_stdio);
		k_data->key++;
		//! Тут все зафришить!!!!!!
	}
}

void			minishell_history_close(struct s_key_data *k_data)
{
	char *key;

	key = ft_itoa(k_data->key);
	ft_printf("k_data->key: %d\n", k_data->key);
	close(k_data->fd_ms_history);
	W_FVAL(MRC, KEY_LAST_CMD_MHISTORY, key);
	ft_strdel(&k_data->key_str);
	ft_strdel(&key);
}

void			minishell_history_init(struct s_key_data *k_data)
{
	mode_t		st_mode;

	st_mode = 0;
	st_mode = S_IRWXU | S_IRGRP | S_IROTH;
	k_data->key_str = R_FVAL(MRC, KEY_LAST_CMD_MHISTORY);
	k_data->key = ft_atoi(k_data->key_str);
	k_data->fd_ms_history = open(MHISTORY, O_CREAT | O_WRONLY | O_APPEND, st_mode);
}
