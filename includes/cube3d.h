/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:24:03 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/22 19:59:00 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <mlx.h>
# include <math.h>

# include "../utils/libft/libft.h"

# define BLACK		"\033[0;30m"
# define RED		"\033[0;31m"
# define GREEN		"\033[0;32m"
# define YELLOW		"\033[0;33m"
# define BLUE		"\033[0;34m"
# define MAGENTA	"\033[0;35m"
# define CYAN		"\033[0;36m"
# define WHITE		"\033[0;37m"
# define RESET		"\033[0m"
# define BOLD		"\033[1m"
# define BOLD_RED	"\033[1;31m"
# define BOLD_GREEN	"\033[1;32m"
# define BOLD_BLUE	"\033[1;34m"
# define BOLD_WHITE	"\033[1;37m"
# define RESET		"\033[0m"
# define MALLOC_ERR "Malloc Error\n"
# define IMG_ERR "Error while loading img\n"

//TEMP INCLUDE
char	**generate_map(int width, int height);
void	print_map(char **map, int height);

typedef struct s_ray
{
	int		col;
	double	angle;
	double	distance;
	int		max;
	double	x;
	double	y;
	int		map_x;
	int		map_y;
	double	dist_corr;
	double	wall_height;
}	t_ray;

typedef struct s_keys
{
	int	view_left;
	int	view_right;
	int	left;
	int	right;
	int	up;
	int	down;
}	t_keys;

typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	double		x;
	double		y;
	double		r;
	double		fov;
	t_img		data_img;
}	t_player;

typedef struct s_minimap
{
	void	*wall;
	void	*wall_addr;
	int		wall_bpp;
	int		wall_size_line;
	void	*door;
	void	*door_addr;
	int		door_bpp;
	int		door_size_line;
}	t_minimap;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;

typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_img		vision;
	t_keys		keys;
	t_map		*map;
	t_minimap	*minimap;
	t_player	*player;
}	t_data;

int		close_hook(void *param);
int		key_press(int keycode, t_data *data);
int		key_release(int keycode, t_data *data);
int		loop_hook(t_data *data);
int		can_moove(t_data *data, double dx, double dy);
int		load_img(t_data *data);

void	init_player(t_data *data);
void	draw_player_arrow(t_data *data, int width);
void	raycasting(t_data *data);
void	my_mlx_pixel_put(t_img *data, int x, int y, int color);
void	load_minimap(t_data *data);
void	render_frame(t_data *data);
void	door_draw_wall(t_data *data, int col, double wallHeight, double hitPos);
void	draw_wall(t_data *data, int col, double wall_height, double hitPos);
void	exit_game(t_data *data);
void	free_map(char **map, int height);
void	*error_handler(t_data *data, int id);

#endif
