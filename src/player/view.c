/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:29:56 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/26 19:13:55 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	raycasting3(t_data *data, t_ray *vars)
{
	if (data->map->map[vars->map_y][vars->map_x] == 'P'
		|| data->map->map[vars->map_y][vars->map_x] == 'p')
	{
		vars->dist_corr = vars->distance * cos(vars->angle
				- (data->player->r * 3.14159265 / 180.0));
		if (vars->dist_corr <= 0.1)
			vars->dist_corr = 0.1;
		vars->wall_height = (1080.0 * 32.0) / vars->dist_corr;
		if (vars->map_x != (int)floor(vars->x))
			vars->hitpos = fmod(vars->y + 32.0, 32.0) / 32.0;
		else
			vars->hitpos = fmod(vars->x + 32.0, 32.0) / 32.0;
		if (!door_is_solid(data, vars,
				data->map->map[vars->map_y][vars->map_x]))
			return (0);
		door_draw_wall(data, vars, data->map->map[vars->map_y][vars->map_x]);
		return (1);
	}
	return (0);
}

int	raycasting4(t_data *data, t_ray *vars)
{
	vars->x = data->player->x + cos(vars->angle) * vars->distance;
	vars->y = data->player->y + sin(vars->angle) * vars->distance;
	vars->map_x = (int)floor(vars->x / 32);
	vars->map_y = (int)floor(vars->y / 32);
	if (vars->map_x != vars->prev_map_x)
		vars->side = 0;
	else
		vars->side = 1;
	vars->prev_map_x = vars->map_x;
	vars->prev_map_y = vars->map_y;
	if (vars->map_x < 0 || vars->map_y < 0
		|| vars->map_x >= data->map->width || vars->map_y >= data->map->height)
		return (1);
	if (raycasting2(data, vars) == 1)
		return (1);
	return (0);
}

void	raycasting(t_data *data)
{
	t_ray	vars;

	if (data->map->width > data->map->height)
		vars.max = data->map->width;
	else
		vars.max = data->map->height;
	vars.col = 0;
	vars.prev_map_x = (int)floor(data->player->x / 32);
	vars.prev_map_y = (int)floor(data->player->y / 32);
	while (vars.col < 1920)
	{
		vars.angle = (data->player->r - data->player->fov / 2.0
				+ ((double)vars.col / 1920.0)
				* data->player->fov) * 3.14159265 / 180.0;
		vars.distance = 0.0;
		while (vars.distance < vars.max * 32)
		{
			if (raycasting4(data, &vars) == 1)
				break ;
			vars.distance += 0.5;
		}
		vars.col++;
	}
}

void	render_frame(t_data *data)
{
	int	x;
	int	y;

	y = 0;
	while (y < 1080)
	{
		x = 0;
		while (x < 1920)
		{
			if (y < 1080 / 2)
				my_mlx_pixel_put(&data->vision, x, y, 0x77b5fe);
			else
				my_mlx_pixel_put(&data->vision, x, y, 0x000000);
			x++;
		}
		y++;
	}
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->vision.img, 0, 0);
	draw_player_arrow(data, 0);
	load_minimap(data);
}
