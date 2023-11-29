#ifndef CUB3D_H
# define CUB3D_H

# include "../include/get_next_line/get_next_line.h"
# include "../include/libft/libft.h"
# include "../include/mlx/mlx.h"
# include <fcntl.h>
# include <stdio.h>
# include <math.h>

#  define WIDTH 1024
#  define HEIGHT 512
#  define PI 3.1415926535

typedef struct s_ray
{
	int		id;
	int		hr_x;
	int		hr_y;
	double	len_h;
	int 	vr_x;
	int 	vr_y;
	double len_v;
	double	r_a;
}			t_ray;

typedef struct s_map
{
	char	**map;
	char	**map2;
	char	*so;
	char	*no;
	char	*we;
	char	*ea;
	int		*c;
	int		*f;
	int		i;
	double	p_col;
	double	p_row;
	char	type;
	int		count;
	int		map_row;
	int		map_col;
}			t_map;

typedef struct s_data
{
	t_map	map;
}			t_data;


typedef struct s_mlx
{
	void *mlx_ptr;
	void *win_ptr;
	void *fl_ptr;
	void *cl_ptr;
	void *pl_ptr;
	void *img_ptr;
	void *s_img_ptr;
	void *n_img_ptr;
	void *n_s_img_ptr;
	void *path_ptr;
	void *wall_ptr;
	int		pl_x;
	int 	pl_y;
	float	pl_dx;
	float	pl_dy;
	float	pl_a;
	char **map;
	t_ray	*ray;
} t_mlx;

char		*ft_ret(char *str);
void		ft_err(void);
int			ft_wh_sp(char c);
int			count_wd(char *s);
int			count_comma(char *s);
int			ft_sp_ctrl(char *str);
void		path_check(t_data *fc);
void		control2(t_data *data, char *str);
int			*ft_ret_fc(char *str, char c);
void		ft_nosw(char *str, t_data *game);
void		ft_get_map2(t_data *data);
void		map_free(char **map);
char		*ft_strjoin_v2(char *str, char buffer, int len);
int			map_lines(char *str);
void		manipulate_image(void *img_ptr, int color[3], int width, int height);
void		load_map(t_mlx *data);
void		init_window(t_mlx *data);
void		init_map(t_mlx *data);
void		put_map(t_mlx *data);
void		init_game(t_mlx *data);
void		init_background(t_mlx *data);
void		init_player(t_mlx *data);
int			mv_player(int key, t_mlx *data);
void		put_game_bg(t_mlx *data);

#endif