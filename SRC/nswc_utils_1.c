/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   nswc_utils_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 00:43:50 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/19 07:06:08 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	del_wspace(char **str)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while ((*str)[i])
	{
		if ((*str)[i] != ' ')
		{
			(*str)[j] = (*str)[i];
			j++;
		}
		i++;
	}
	(*str)[j] = '\0';
}

int	count_comma(char *s)
{
	int	count;

	count = 0;
	while (*s)
	{
		if (*s == ',')
			count++;
		s++;
	}
	return (count);
}

int	count_wd(char *s)
{
	int	i;
	int	count;

	count = 0;
	i = -1;
	while (s[++i])
		if (!ft_isdigit(s[i]) && s[i] != ',' && s[i] != '\n' && s[i] != ' ')
			ft_err();
	
	i = 0;
	while (s[i])
	{
		while (s[i] == ',' || s[i] == ' ')
			i++;
		if(s[i] == '\n')
			break;
		if (s[i])
			count++;
		while (s[i] && s[i] != ' ' && s[i] != ',')
			i++;
	}
	del_wspace(&s);
	if (!ft_isdigit(*s))
		ft_err();
	while (*s)
	{
		if (*s == ',' && *(s + 1) == ',')
			ft_err();
		if (*s == ',' && (*(s + 1) == '\n'))
			ft_err();
		s++;
	}
	return (count);
}

int	ft_sp_ctrl(char *str)
{
	int	i;
	int	flag;

	i = 0;
	flag = 0;
	while (str[i] && str[i] != '\n')
	{
		if (str[i] != 32)
		{
			flag = 1;
			break ;
		}
		i++;
	}
	if (str[i] == '\n' && ft_strlen(str) == 1)
		flag = 1;
	return (flag);
}

void	control2(t_data *data, char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_wh_sp(str[i]))
			i++;
		else
			break ;
	}
	if (!ft_strncmp(str + i, "F", 1))
		data->map.f = ft_ret_fc(str + i, 'F');
	if (!ft_strncmp(str + i, "C", 1))
		data->map.c = ft_ret_fc(str + i, 'C');
}

void	ft_err(void)
{
	printf("Error\n");
	exit(1);
}
