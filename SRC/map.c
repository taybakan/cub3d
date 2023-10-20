/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 10:39:47 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/19 07:37:10 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	printmap(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		printf("%s\n", map[i]);
		i++;
	}
}
char	*ft_change(char *str, t_data *data)
{
	char	*a;

	a = ft_strjoin_v2(str, '*', data->map.map_col);
	return (a);
}

char	*yildizkoy(char **map)
{
	int		yildizsayisi;
	int		enuzunsatir;
	char	*yildizlisatir;

	yildizsayisi = 0;
	enuzunsatir = 0;
	yildizsayisi = (int)ft_strlen(map[enuzunsatir]);
	while (map[enuzunsatir])
	{
		if (yildizsayisi < (int)ft_strlen(map[enuzunsatir]))
			yildizsayisi = (int)ft_strlen(map[enuzunsatir]);
		enuzunsatir++;
	}
	yildizlisatir = malloc(yildizsayisi + 1);
	yildizlisatir[yildizsayisi + 1] = 0;
	enuzunsatir = 0;
	while (yildizsayisi >= 0)
	{
		yildizlisatir[enuzunsatir++] = '*';
		yildizsayisi--;
	}
	return (yildizlisatir);
}

void	putstar(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == ' ')
				map[i][j] = '*';
			j++;
		}
		j = 0;
		i++;
	}
}

void	haritasonkontrol(char **map)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			if (map[i][j] == '*' && map[i][j + 1])
				if (map[i][j + 1] == '0')
					ft_err();
			if (map[i][j] == '*' && map[i + 1])
				if (map[i + 1][j] == '0')
					ft_err();
			if (map[i][j] == '*' && map[i][j - 1])
				if (map[i][j - 1] == '0')
					ft_err();
			j++;
		}
		j = 0;
		i++;
	}
}

void	check_valid_map(char **map, t_data *data)
{
	int		i;
	char	**str;
	char	*yildizlisatir;

	i = 1;
	str = ft_calloc(sizeof(char *) * data->map.map_col + 2, 1);
	yildizlisatir = yildizkoy(map);
	str[0] = yildizlisatir;
	while (map[i])
	{
		str[i] = ft_change(map[i], data);
		i++;
	}
	str[i] = ft_strdup(yildizlisatir);
	str[i + 1] = NULL;
	putstar(str);
	printmap(str);
	haritasonkontrol(str);
	map_free(str);
}

char	**duplicate_to_map(t_data *data)
{
	char	**copy;
	int		i;

	copy = malloc(sizeof(char *) * (data->map.map_row + 1));
	if (!copy)
		return (NULL);
	i = 0;
	while (data->map.map2[i])
	{
		copy[i] = ft_strdup(data->map.map2[i]);
		i++;
	}
	copy[i] = NULL;
	return (copy);
}

void	ctrl(t_data *data)
{
	char	**str;
	int		i;
	int		a;
	size_t	tmp;

	str = data->map.map2;
	i = -1;
	while (str[++i])
	{
		if (ft_strlen(str[i]) > tmp)
			a = ft_strlen(str[i]);
		tmp = a;
	}
	data->map.map_col = a;
}

void	ft_get_map2(t_data *data)
{
	char	**str;
	char	**copy;
	int		i;
	int		j;
	int		k;

	str = data->map.map2;
	i = 0;
	while (ft_strlen(str[i]) == 1)
		i++;
	k = i;
	while (str[++i])
	{
		//if (ft_sp_ctrl(str[i]) == 0 || ft_strlen(str[i]) == 1)
		//	ft_err();
		j = -1;
		while (str[i][++j])
		{
			if (str[i][j] == 'N' || str[i][j] == 'W' || str[i][j] == 'E'
				|| str[i][j] == 'S')
			{
				data->map.type = str[i][j];
				data->map.count++;
				data->map.p_row = (double)i - (double)k;
				data->map.p_col = (double)j;
			}
		}
	}
	ctrl(data);
	if (data->map.count != 1)
		ft_err();
	copy = duplicate_to_map(data);
	check_valid_map(copy, data);
	map_free(copy);
}
