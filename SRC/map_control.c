/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_control.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fsoymaz <fsoymaz@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:49:43 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/10/20 13:04:59 by fsoymaz          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"


void	path_basket(t_data *fc)
{
	if (!ft_strncmp(fc->map.ea, fc->map.so, ft_strlen(fc->map.ea))
		|| !ft_strncmp(fc->map.ea, fc->map.no, ft_strlen(fc->map.ea))
		|| !ft_strncmp(fc->map.ea, fc->map.we, ft_strlen(fc->map.ea))
		|| !ft_strncmp(fc->map.no, fc->map.so, ft_strlen(fc->map.no))
		|| !ft_strncmp(fc->map.no, fc->map.we, ft_strlen(fc->map.no))
		|| !ft_strncmp(fc->map.we, fc->map.so, ft_strlen(fc->map.so)))
		ft_err();
}

void	path_check(t_data *fc)
{
	if (ft_strncmp(fc->map.we, "./", 2) || ft_strncmp(fc->map.so, "./", 2)
		|| ft_strncmp(fc->map.ea, "./", 2) || ft_strncmp(fc->map.no, "./", 2))
		ft_err();
	if (open(fc->map.we + 2, O_RDWR, 0777) == -1 || open(fc->map.so + 2, O_RDWR,
			0777) == -1 || open(fc->map.ea + 2, O_RDWR, 0777) == -1
		|| open(fc->map.no + 2, O_RDWR, 0777) == -1)
		ft_err();
	path_basket(fc);
}
