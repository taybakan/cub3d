/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taybakan <taybakan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/20 20:06:25 by taybakan          #+#    #+#             */
/*   Updated: 2023/10/20 20:16:44 by taybakan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

void manipulate_image(void *img_ptr, int color[3], int width, int height)
{
	int *data;
	int bits_per_pixel;
	int size_line;
	int endian;
	
	data = (int *)mlx_get_data_addr(img_ptr, &bits_per_pixel, &size_line, &endian);

	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int pixel_index = (y * size_line / 4) + x;
			int pixel_color = (0 << 24) | (color[0] << 16) | (color[1] << 8) | color[2];
			data[pixel_index] = pixel_color;
		}
	}
}
