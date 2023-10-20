/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/19 03:58:39 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/20 13:05:26 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void	map_free(char **map)
{
	int	i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

char	*ft_strjoin_v2(char *str, char buffer, int len)
{
	char	*result;
	int		i;
	int		j;

	i = 0;
	j = 1;
	result = malloc(sizeof(char) * len + 2);
	if (!result)
		return (NULL);
	result[0] = '*';
	while (str[i] && str[i] != '\n')
	{
		result[j] = str[i];
		j++;
		i++;
	}
	while (j < len)
	{
		result[j] = buffer;
		j++;
	}
	result[j++] = '*';
	result[j] = '\0';
	return (result);
}

int	map_lines(char *str)
{
	char	*line;
	int		fd;
	int		i;

	i = 0;
	fd = open(str, O_RDONLY);
	line = get_next_line(fd);
	if (line == NULL)
		ft_err();
	while (line)
	{
		free(line);
		i++;
		line = get_next_line(fd);
	}
	close(fd);
	return (i);
}


int	ft_wh_sp(char c)
{
	if ((c <= 13 && c >= 9) || c == 32)
		return (1);
	return (0);
}