/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   work_color.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ksharlen <ksharlen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 09:05:43 by ksharlen          #+#    #+#             */
/*   Updated: 2019/09/17 09:59:02 by ksharlen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ls.h"

void	def_font(char *color, const char ls_color)
{
	if (ls_color >= 'A' && ls_color <= 'Z')
		ft_strcat(color, "01m");
	else
		ft_strcat(color, "22m");
}

void	def_backgrnd(char *color, const char ls_color)
{
	if (ls_color == 'a' || ls_color == 'A')
		ft_strcat(color, "40;");
	else if (ls_color == 'b' || ls_color == 'B')
		ft_strcat(color, "41;");
	else if (ls_color == 'c' || ls_color == 'C')
		ft_strcat(color, "42;");
	else if (ls_color == 'd' || ls_color == 'D')
		ft_strcat(color, "43;");
	else if (ls_color == 'e' || ls_color == 'E')
		ft_strcat(color, "44;");
	else if (ls_color == 'f' || ls_color == 'F')
		ft_strcat(color, "45;");
	else if (ls_color == 'g' || ls_color == 'G')
		ft_strcat(color, "46;");
	else if (ls_color == 'h' || ls_color == 'H')
		ft_strcat(color, "47;");
	else
		ft_strcat(color, "49;");
}

void	def_color(char *color, const char ls_color)
{
	if (ls_color == 'a' || ls_color == 'A')
		ft_strcpy(color, "\e[30;");
	else if (ls_color == 'b' || ls_color == 'B')
		ft_strcpy(color, "\e[31;");
	else if (ls_color == 'c' || ls_color == 'C')
		ft_strcpy(color, "\e[32;");
	else if (ls_color == 'd' || ls_color == 'D')
		ft_strcpy(color, "\e[33;");
	else if (ls_color == 'e' || ls_color == 'E')
		ft_strcpy(color, "\e[34;");
	else if (ls_color == 'f' || ls_color == 'F')
		ft_strcpy(color, "\e[35;");
	else if (ls_color == 'g' || ls_color == 'G')
		ft_strcpy(color, "\e[36;");
	else if (ls_color == 'h' || ls_color == 'H')
		ft_strcpy(color, "\e[37;");
	else
		ft_strcpy(color, "\e[39;");
}
