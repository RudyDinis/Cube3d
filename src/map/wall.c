/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:37:31 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/27 10:31:53 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	get_pixel_color(t_data *data, int x, int y, int face)
{
	char	*pixel;

	if (y < 0)
		y = 0;
	if (y > 31)
		y = 31;
	if (face == 0)
		pixel = data->minimap->wall_addr_no + (y
				* data->minimap->wall_size_line_no + x
				* (data->minimap->wall_bpp_no / 8));
	if (face == 1)
		pixel = data->minimap->wall_addr_so + (y
				* data->minimap->wall_size_line_so + x
				* (data->minimap->wall_bpp_so / 8));
	if (face == 2)
		pixel = data->minimap->wall_addr_ea + (y
				* data->minimap->wall_size_line_ea + x
				* (data->minimap->wall_bpp_ea / 8));
	if (face == 3)
		pixel = data->minimap->wall_addr_we + (y
				* data->minimap->wall_size_line_we + x
				* (data->minimap->wall_bpp_we / 8));
	return (*(unsigned int *)pixel);
}

void	draw_wall(t_data *data, t_ray *vars, int face)
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
		my_mlx_pixel_put(&data->vision, vars->col, y, get_pixel_color(data,
				(int)(vars->hitpos * 32), (int)tex_pos & 31, face));
		tex_pos += step;
		y++;
	}
}

void	raycasting22(t_ray *vars, int *face)
{
	if (vars->side == 0)
	{
		if (cos(vars->angle) > 0)
			*face = 3;
		else
			*face = 2;
		vars->hitpos = fmod(vars->y + 32.0, 32.0) / 32.0;
	}	
	else
	{
		if (sin(vars->angle) > 0)
			*face = 0;
		else
			*face = 1;
		vars->hitpos = fmod(vars->x + 32.0, 32.0) / 32.0;
	}
}

int	raycasting2(t_data *data, t_ray *vars)
{
	int		face;

	if (data->map->map[vars->map_y][vars->map_x] == '1')
	{
		vars->dist_corr = vars->distance * cos(vars->angle
				- (data->player->r * 3.14159265 / 180.0));
		if (vars->dist_corr <= 0.1)
			vars->dist_corr = 0.1;
		raycasting22(vars, &face);
		vars->wall_height = (1080.0 * 32.0) / vars->dist_corr;
		vars->zbuffer[vars->col] = vars->dist_corr;
		draw_wall(data, vars, face);
		return (1);
	}
	if (raycasting3(data, vars) == 1)
		return (1);
	return (0);
}
