/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   door.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 12:51:04 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/23 15:33:01 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	door_get_pixel_color(t_data *data, int x, int y, char p)
{
	char	*pixel;

	if (y < 0)
		y = 0;
	if (y > 31)
		y = 31;
	if (p == 'P')
		pixel = data->minimap->door_c_addr
			+ (y * data->minimap->door_c_size_line
				+ x * (data->minimap->door_c_bpp / 8));
	if (p == 'p')
		pixel = data->minimap->door_o_addr
			+ (y * data->minimap->door_o_size_line
				+ x * (data->minimap->door_o_bpp / 8));
	return (*(unsigned int *)pixel);
}

int	door_is_solid(t_data *data, t_ray *vars, char p)
{
	int	tex_x;
	int	tex_y;
	int	color;

	tex_x = (int)(vars->hitpos * 31);
	tex_y = 16;
	color = door_get_pixel_color(data, tex_x, tex_y, p);
	if (color == 16711808)
		return (0);
	return (1);
}

void	interact_door2(t_data *data, int x, int y)
{
	if (data->map->map[y][x] == 'P')
	{
		printf("opening door\n");
		data->map->map[y][x] = 'p';
	}
	else if (data->map->map[y][x] == 'p')
	{
		printf("closing door\n");
		data->map->map[y][x] = 'P';
	}
}

void	interact_door(t_data *data)
{
	float	angle;
	int		x;
	int		y;

	y = data->player->y / 32;
	x = data->player->x / 32;
	angle = fmod(data->player->r, 360.0f);
	if (angle < 0)
		angle += 360.0f;
	if (angle <= 200 && angle >= 155)
		interact_door2(data, x - 1, y);
	if ((angle >= 340 && angle <= 360) || (angle >= 0 && angle <= 20))
		interact_door2(data, x + 1, y);
}

void	door_draw_wall(t_data *data, t_ray *vars, char p)
{
	int		y;
	int		y_start;
	int		y_end;
	double	step;
	double	tex_pos;

	y_start = (1080 / 2) - (int)(vars->wall_height / 2);
	y_end = (1080 / 2) + (int)(vars->wall_height / 2);
	if (y_start < 0)
		y_start = 0;
	if (y_end > 1080)
		y_end = 1080;
	step = 32.0 / vars->wall_height;
	tex_pos = (y_start - 1080 / 2 + vars->wall_height / 2) * step;
	y = y_start;
	while (y < y_end)
	{
		tex_pos += step;
		vars->color = door_get_pixel_color(data,
				(int)(vars->hitpos * 32), (int)tex_pos & 31, p);
		if (vars->color != 16711808)
			my_mlx_pixel_put(&data->vision, vars->col, y, vars->color);
		y++;
	}
}
