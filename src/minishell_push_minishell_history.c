/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_push_minishell_history.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 16:45:31 by ksharlen          #+#    #+#             */
/*   Updated: 2019/10/05 12:36:22 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		getkey_internal(struct s_key_data *key)
{
	key->key_str = R_FVAL(MRC, KEY_LAST_CMD_MHISTORY);
	key->key = ft_atoi(key->key_str);
}

static void	getdate_internal(char *date_ex_cmd)
{
	time_t		date_ex;
	char		*str_date;

	if (time(&date_ex) == RET_ERROR)
		err_exit(E_TIME, "minishell");
	if (!(str_date = ctime(&date_ex)))
		err_exit(E_CTIME, "minishell");
	ft_memcpy(date_ex_cmd, str_date, ft_strlen(str_date) - 1);
}

void		minishell_push_minishell_history(const char *str_stdio,
	struct s_key_data *k_data)
{
	if (str_stdio && k_data && *str_stdio && k_data->key_str)
	{
		ft_bzero(k_data->date_ex_cmd, SIZE_DATE + 1);
		getdate_internal(k_data->date_ex_cmd);
		ft_printf("%v%d:[%s];%s\n", k_data->fd_ms_history,
			k_data->key, k_data->date_ex_cmd, str_stdio);
		k_data->key++;
	}
}

void		minishell_history_close(struct s_key_data *k_data)
{
	char *key;

	key = ft_itoa(k_data->key);
	if (!key)
		err_exit(E_MALLOC, "minishell");
	if (close(k_data->fd_ms_history) == RET_ERROR)
		err_exit(E_CLOSE, "minishell");
	W_FVAL(MRC, KEY_LAST_CMD_MHISTORY, key);
	ft_strdel(&k_data->key_str);
	ft_strdel(&key);
}

void		minishell_history_init(struct s_key_data *k_data)
{
	mode_t		st_mode;
	int			fd;

	st_mode = 0;
	st_mode = S_IRUSR | S_IWUSR | S_IRGRP | S_IROTH;
	k_data->key_str = R_FVAL(MRC, KEY_LAST_CMD_MHISTORY);
	if (!k_data->key_str)
	{
		if ((fd = open(g_path.P_MSRC, O_CREAT | O_WRONLY | O_APPEND,
			st_mode)) == RET_ERROR)
			err_exit(E_OPEN, "minishell");
		ft_printf("%v%s=%s", fd, KEY_LAST_CMD_MHISTORY, "0");
		k_data->key = 0;
		k_data->key_str = ft_strdup("0");
		if (close(fd) == RET_ERROR)
			err_exit(E_CLOSE, "minishell");
	}
	else
		k_data->key = ft_atoi(k_data->key_str);
	if ((k_data->fd_ms_history = open(g_path.P_MSHIST, O_CREAT | O_WRONLY | O_APPEND,
		st_mode)) == RET_ERROR)
		err_exit(E_OPEN, "minishell");
}
