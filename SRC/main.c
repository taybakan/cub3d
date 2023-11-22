/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: taybakan <taybakan@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/14 19:34:44 by fsoymaz           #+#    #+#             */
/*   Updated: 2023/11/22 17:22:03 by taybakan         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"
#include <stdio.h>

void draw_line(void *mlx_ptr, void *win_ptr, int x0, int y0, int x1, int y1)
{
	int dx = abs(x1 - x0);
	int dy = abs(y1 - y0);
	int sx = (x0 < x1) ? 1 : -1;
	int sy = (y0 < y1) ? 1 : -1;
	int err = dx - dy;

	while (1)
	{
		mlx_pixel_put(mlx_ptr, win_ptr, x0, y0, 0xFFFFFF);

		if (x0 == x1 && y0 == y1)
		{
			break;
		}
		int e2 = 2 * err;
		if (e2 > -dy)
		{
			err = err - dy;
			x0 = x0 + sx;
		}
		if (e2 < dx)
		{
			err = err + dx;
			y0 = y0 + sy;
		}
	}
}

void	draw_rays(t_mlx *data)
{
	int end_x;
	int end_y;

	for (int i = data->pl_a; i < (data->pl_a + 60); i += 2)
	{
		double angle = i * 6.28319 / 360;
		int line_length = 500;
		end_x = data->pl_x + line_length * cos(angle);
		end_y = data->pl_y + line_length * sin(angle);

		draw_line(data->mlx_ptr, data->win_ptr, data->pl_x, data->pl_y, end_x, end_y);
	}
}

int		mv_player(int key, t_mlx *data)
{
	if (key == 13)
	{
        data->pl_y += (int)(sin(((data->pl_a + 30) * (PI / 180))) * 8);
		data->pl_x += (int)(cos(((data->pl_a + 30) * (PI / 180))) * 8);
	}
    if (key == 1)
	{
		data->pl_y -= (int)(sin(((data->pl_a + 30) * (PI / 180))) * 8);
		data->pl_x -= (int)(cos(((data->pl_a + 30) * (PI / 180))) * 8);
	}
	if (key == 0)
	{
		data->pl_y += (int)(sin(((data->pl_a - 60) * (PI / 180))) * 8);
		data->pl_x += (int)(cos(((data->pl_a - 60) * (PI / 180))) * 8);
	}
	if (key == 2)
	{
		data->pl_y -= (int)(sin(((data->pl_a - 60) * (PI / 180))) * 8);
		data->pl_x -= (int)(cos(((data->pl_a - 60) * (PI / 180))) * 8);
	}
	if (key == 123)
		data->pl_a -= 5;
	if (key == 124)
		data->pl_a += 5;
	mlx_clear_window(data->mlx_ptr, data->win_ptr);
	put_map(data);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->pl_ptr, data->pl_x - 2, data->pl_y - 2);
	draw_rays(data);
	put_game_bg(data);
	return 0;
}

void	init_player(t_mlx *data)
{
	int	i;
	int	j;
	int *pl_rgb;

	data->pl_a = -120;
	pl_rgb = calloc(sizeof(int) * 3, 3);
	pl_rgb[0] = 255;
	data->pl_ptr = mlx_new_image(data->mlx_ptr, 5, 5);
	manipulate_image(data->pl_ptr, pl_rgb, 5, 5);
	i = 0;
	for (int y = 30; y < 512; y += 64)
	{
		j = 0;
		for (int x = 30; x < 512; x += 64)
		{
			if (data->map[i][j] == 'P')
			{
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->pl_ptr, x - 2, y - 2);
				data->pl_x = x;
				data->pl_y = y;
			}
			j++;
		}
		i++;
	}
	draw_rays(data);
}

void	put_game_bg(t_mlx *data)
{
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->fl_ptr, WIDTH / 2, HEIGHT / 2);
	mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->cl_ptr, WIDTH / 2, 0);
}

void	init_background(t_mlx *data)
{
	int *fl_rgb;
	int *cl_rgb;

	data->cl_ptr = mlx_new_image(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);
	data->fl_ptr = mlx_new_image(data->mlx_ptr, WIDTH / 2, HEIGHT / 2);

	fl_rgb = calloc(sizeof(int) * 3, 3);
	cl_rgb = calloc(sizeof(int) * 3, 3);
	fl_rgb[1] = 255;
	cl_rgb[2] = 255;
	manipulate_image(data->fl_ptr, fl_rgb, WIDTH / 2, HEIGHT / 2);
	manipulate_image(data->cl_ptr, cl_rgb, WIDTH / 2, HEIGHT / 2);
}

void	init_game(t_mlx *data)
{
	init_background(data);
	put_game_bg(data);
}

void	put_map(t_mlx *data)
{
	int i;
	int j;
	
	i = 0;
	for (int y = 1; y < 512; y += 64)
	{
		j = 0;
		for (int x = 1; x < 512; x += 64)
		{
			if (data->map[i][j] == '1')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->wall_ptr, x, y);
			if (data->map[i][j] == '0' || data->map[i][j] == 'P')
				mlx_put_image_to_window(data->mlx_ptr, data->win_ptr, data->path_ptr, x, y);
			j++;
		}
		i++;
	}
}

void	init_map(t_mlx *data)
{
	int *wall_rgb;
	int *path_rgb;
	
	data->wall_ptr = mlx_new_image(data->mlx_ptr, 64, 64);
	data->path_ptr = mlx_new_image(data->mlx_ptr, 64, 64);

	wall_rgb = calloc(sizeof(int) * 3, 3);
	path_rgb = calloc(sizeof(int) * 3, 3);
	wall_rgb[0] = 47;
	wall_rgb[1] = 79;
	wall_rgb[2] = 79;
	path_rgb[0] = 112;
	path_rgb[1] = 128;
	path_rgb[2] = 144;
	manipulate_image(data->wall_ptr, wall_rgb, 62, 62);
	manipulate_image(data->path_ptr, path_rgb, 62, 62);
	put_map(data);
}

void	init_window(t_mlx *data)
{
	data->mlx_ptr = mlx_init();
	data->win_ptr = mlx_new_window(data->mlx_ptr, WIDTH, HEIGHT, "cub3d");
	init_map(data);
	init_game(data);
	init_player(data);
	mlx_new_image(data->mlx_ptr, WIDTH, HEIGHT);
}

void	load_map(t_mlx *data)
{
	data->map = malloc(sizeof(char *) * 8);
	data->map[0] = ft_strdup("11111111\0");
	data->map[1] = ft_strdup("10000001\0");
	data->map[2] = ft_strdup("10011001\0");
	data->map[3] = ft_strdup("10000001\0");
	data->map[4] = ft_strdup("11100101\0");
	data->map[5] = ft_strdup("10000001\0");
	data->map[6] = ft_strdup("1P000001\0");
	data->map[7] = ft_strdup("11111111\0");
}

int	ft_exit(void *a)
{
	(void)a;

	exit(0);
	return (0);
}

int	main(void)
{
	t_mlx	*data;

	data = malloc(sizeof(t_mlx));
	load_map(data);
	init_window(data);
	mlx_hook(data->win_ptr, 2, 1L << 0, &mv_player, data);
	mlx_hook(data->win_ptr, 17, 0, &ft_exit, NULL);
	mlx_loop(data->mlx_ptr);
	return (0);
}

//
//int move_player(int keycode, t_dat *dat)
//{
//	int tm = 0;
//	int m = 1;
//	if (keycode == 123) // Left arrow key
//		tm = 100;
//	else if (keycode == 124) // Right arrow key
//		tm = -100;
//	else if (keycode == 125) // Down arrow key
//		m = -10;
//	else if (keycode == 126) // Up arrow key
//		m = 10;
//
//	static int total;
//	int width = 1000;
//	int height = 1000;
//	static  void *tmp = NULL;
//
//	total += tm;
//	
//	if (total == 1500)
//	{
//		total = -1000;
//		if (tmp && tmp != dat->s_img_ptr)
//			dat->s_img_ptr = tmp;
//		else
//		{
//			tmp = dat->s_img_ptr;
//			dat->s_img_ptr = dat->n_s_img_ptr;
//		}
//	}
//	if (total == -1500)
//	{
//		total = 1000;
//		if (tmp && tmp != dat->s_img_ptr)
//			dat->s_img_ptr = tmp;
//		else
//		{
//			tmp = dat->s_img_ptr;
//			dat->s_img_ptr = dat->n_s_img_ptr;
//		}
//	}
//	ft_putnbr_fd(total, 1);
//	ft_putchar_fd('\n', 1);
//	mlx_clear_window(dat->mlx_ptr, dat->win_ptr);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->cl_ptr, 0, 0);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->fl_ptr, 0, height / 2);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, total, height / 3);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, (width / 3) + total, height / 3);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, ((width / 3) * 2) + total, height / 3);
//	mlx_new_image(dat->mlx_ptr, 1000 + total, 1000 + total);
//	return 0;
//}
//
//void resize_image(void *original_img_ptr, void *smaller_img_ptr, int reduction_factor, int original_width, int original_height)
//{
//	int *original_data;
//	int *smaller_data;
//	int original_bits_per_pixel;
//	int original_size_line;
//	int original_endian;
//	int smaller_bits_per_pixel;
//	int smaller_size_line;
//	int smaller_endian;
//
//	original_data = (int *)mlx_get_data_addr(original_img_ptr, &original_bits_per_pixel, &original_size_line, &original_endian);
//	smaller_data = (int *)mlx_get_data_addr(smaller_img_ptr, &smaller_bits_per_pixel, &smaller_size_line, &smaller_endian);
//
//	for (int y = 0; y < original_height; y += reduction_factor)
//	{
//		for (int x = 0; x < original_width; x += reduction_factor)
//		{
//			int original_pixel_index = (y * original_size_line / 4) + x;
//
//			int smaller_x = x / reduction_factor;
//			int smaller_y = y / reduction_factor;
//			int smaller_pixel_index = (smaller_y * smaller_size_line / 4) + smaller_x;
//
//			smaller_data[smaller_pixel_index] = original_data[original_pixel_index];
//		}
//	}
//}
//int main()
//{
//	int width = 1000;
//	int height = 1000;
//	t_dat *dat;
//
//	dat = malloc(sizeof(t_data));
//	dat->mlx_ptr = mlx_init();
//	dat->win_ptr = mlx_new_window(dat->mlx_ptr, 1000, 1000, "Perspective Image");
//	dat->fl_ptr = mlx_new_image(dat->mlx_ptr, width, height / 2);
//	dat->cl_ptr = mlx_new_image(dat->mlx_ptr, width, height / 2);
//	dat->img_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, "./textures/a.xpm", &width, &height);
//	dat->s_img_ptr = mlx_new_image(dat->mlx_ptr, width / 3, height / 3);
//	dat->n_img_ptr = mlx_xpm_file_to_image(dat->mlx_ptr, "./textures/b.xpm", &width, &height);
//	dat->n_s_img_ptr = mlx_new_image(dat->mlx_ptr, width / 3, height / 3);
//	// Error handling for img_ptr being NULL should be added here
//
//	manipulate_image(dat->fl_ptr, 2, width, height / 2);
//	manipulate_image(dat->cl_ptr, 3, width, height / 2);
//	resize_image(dat->img_ptr, dat->s_img_ptr, 3, width, height);
//	resize_image(dat->n_img_ptr, dat->n_s_img_ptr, 3, width, height);
//
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->cl_ptr, 0, 0);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->fl_ptr, 0, height / 2);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, 0, height / 3);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, (width / 3), height / 3);
//	mlx_put_image_to_window(dat->mlx_ptr, dat->win_ptr, dat->s_img_ptr, (width / 3) * 2, height / 3);
//	mlx_hook(dat->win_ptr, 2, 1L << 0, &move_player, dat);
//	mlx_loop(dat->mlx_ptr);
//	return 0;
//}
//