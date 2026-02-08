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
	if (x > 1920)
		printf("starfoula");
	if (y > 1920)
		printf("oulala");

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

void	background(t_data *data)
{
	int			y;
	int			x;

	x = 0;
	y = 0;
	while (x < 32)
	{
		y = 0;
		while (y < 32)
		{
			my_mlx_pixel_put(&data->player->data_img, x, y, 0x000000);
			y++;
		}
		x++;
	}
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
	background(data);
	while (i < 14)
	{
		width = (10 * (14 - i)) / 10;
		j = -width;
		while (j < width)
		{
			x = 14 + (int)(cos(angle_rad) * i - sin(angle_rad) * j);
			y = 14 - (int)(sin(angle_rad) * i + cos(angle_rad) * j);
			my_mlx_pixel_put(&data->player->data_img, x, y, 0x00FFDE21);
			j++;
		}
		i++;
	}
	mlx_put_image_to_window(data->mlx, data->mlx_win,
		data->player->data_img.img, (int)data->player->x, (int)data->player->y);
}

void	init_player(t_data *data)
{
	t_img	*data_img;

	data_img = &data->player->data_img;
	data_img->img = mlx_new_image(data->mlx, 32, 32);
	data_img->addr = mlx_get_data_addr(data_img->img, &data_img->bits_per_pixel,
			&data_img->line_length, &data_img->endian);
	data->player->x = 32 * 2 + 16;
	data->player->y = 32 * 2 + 16;
	data->player->r = 0;
	data->player->fov = 60;
	draw_player_arrow(data, 0);
}
