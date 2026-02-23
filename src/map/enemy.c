/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 18:59:08 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/23 19:28:54 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	enemy_get_pixel_color(t_data *data, int x, int y)
{
	char	*pixel;

	if (y < 0)
		y = 0;
	if (y > 63)
		y = 63;
	pixel = data->enemy->img.addr + (y * data->enemy->img.line_length
			+ x * (data->enemy->img.bits_per_pixel / 8));
	return (*(unsigned int *)pixel);
}

void	draw_enemy(t_data *data, t_ray *vars)
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
	step = 64.0 / vars->wall_height;
	tex_pos = (y_start - 1080 / 2 + vars->wall_height / 2) * step;
	y = y_start;
	while (y < y_end)
	{
		vars->color = enemy_get_pixel_color(
				data, (int)(vars->hitpos * 64), (int)tex_pos & 63);
		if (vars->color != 9961608)
			my_mlx_pixel_put(&data->vision, vars->col, y, vars->color);
		tex_pos += step;
		y++;
	}
}
