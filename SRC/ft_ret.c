/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ret.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 13:04:09 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/20 13:05:15 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

char	**ft_ret_fc_next(char *str, char **split, int res, char c)
{
	int	i;

	i = 0;
	i = 0;
	while (ft_wh_sp(str[i]))
		i++;
	if (str[i] == c && str[i + 1] == 32)
	{
		i++;
		while (str[i] == 32)
			i++;
	}
	else
		ft_err();
	res = count_wd(str + i);
	if (res != 3)
		ft_err();
	split = ft_split(str + i, ',');
	return (split);
}

int	*ft_ret_fc(char *str, char c)
{
	int		comma;
	char	**split;
	int		res;
	int		*a;

	res = 0;
	split = NULL;
	a = malloc(sizeof(int) * 3);
	comma = count_comma(str);
	if (comma != 2)
		ft_err();
	else if (comma == 2)
		split = ft_ret_fc_next(str, split, res, c);
	a[0] = ft_atoi(split[0]);
	a[1] = ft_atoi(split[1]);
	a[2] = ft_atoi(split[2]);
	if (a[0] > 255 || a[1] > 255 || a[2] > 255)
		ft_err();
	map_free(split);
	return (a);
}

void	ft_check(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == 'm' && str[i - 1] == 'p' && str[i - 2] == 'x')
			break ;
		i++;
	}
	while (str[++i])
	{
		if (!ft_wh_sp(str[i]) && str[i] != '\n')
			ft_err();
	}
}

char	*ft_ret(char *str)
{
	int		i;
	char	*a;

	i = 0;
	while (str[i])
	{
		if (str[i] == 32)
			i++;
		else if (str[i] == '.' && ft_wh_sp(str[i - 1]))
			break ;
		else
			ft_err();
	}
	ft_check(str);
	a = ft_strtrim(str, " \n");
	return (a);
}