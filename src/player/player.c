/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 19:13:20 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/07 19:57:56 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	my_mlx_pixel_put(t_img *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	draw_player_arrow(t_data *data, int width)
{
	double	angle_rad;
	int		x;
	int		y;
	int		i;
	int		j;

	i = 0;
	angle_rad = (data->player->r * 3.14159265) / 180.0;
	while (i < 16)
	{
		width = (10 * (16 - i)) / 10;
		j = -width;
		while (j < width)
		{
			x = 16 + (int)(cos(angle_rad) * i - sin(angle_rad) * j);
			y = 16 - (int)(sin(angle_rad) * i + cos(angle_rad) * j);
			my_mlx_pixel_put(&data->player->data_img, x, y, 0x00FFDE21);
			j++;
		}
		i++;
	}
}

void	init_player(t_data *data)
{
	t_img	*data_img;

	data_img = &data->player->data_img;
	data_img->img = mlx_new_image(data->mlx, 32, 32);
	data_img->addr = mlx_get_data_addr(data_img->img, &data_img->bits_per_pixel,
			&data_img->line_length, &data_img->endian);
	draw_player_arrow(data, 0);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data_img->img, 0, 0);
}
