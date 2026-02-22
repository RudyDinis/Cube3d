/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   wall.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:37:31 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/22 16:25:27 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	get_pixel_color(t_data *data, int x, int y)
{
	char	*pixel;

	if (y < 0)
		y = 0;
	if (y > 31)
		y = 31;
	pixel = data->minimap->wall_addr + (y * data->minimap->wall_size_line
			+ x * (data->minimap->wall_bpp / 8));
	return (*(unsigned int *)pixel);
}

void	draw_wall(t_data *data, int col, double wall_height, double hitPos)
{
	int		y;
	int		y_start;
	int		y_end;
	double	step;
	double	tex_pos;

	y_start = (1080 / 2) - (int)(wall_height / 2);
	y_end = (1080 / 2) + (int)(wall_height / 2);
	if (y_start < 0)
		y_start = 0;
	if (y_end > 1080)
		y_end = 1080;
	step = 32.0 / wall_height;
	tex_pos = (y_start - 1080 / 2 + wall_height / 2) * step;
	y = y_start;
	while (y < y_end)
	{
		tex_pos += step;
		my_mlx_pixel_put(&data->vision, col, y, get_pixel_color(data,
				(int)(hitPos * 32), (int)tex_pos & 31));
		y++;
	}
}
