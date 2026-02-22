/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   event.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:18:42 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/22 19:23:15 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	key_press(int keycode, t_data *data)
{
	if (keycode == 65361)
		data->keys.view_left = 1;
	if (keycode == 65363)
		data->keys.view_right = 1;
	if (keycode == 119)
		data->keys.up = 1;
	if (keycode == 115)
		data->keys.down = 1;
	if (keycode == 100)
		data->keys.right = 1;
	if (keycode == 97)
		data->keys.left = 1;
	if (keycode == 65307)
		close_hook(data);
	return (0);
}

int	key_release(int keycode, t_data *data)
{
	if (keycode == 65361)
		data->keys.view_left = 0;
	if (keycode == 65363)
		data->keys.view_right = 0;
	if (keycode == 119)
		data->keys.up = 0;
	if (keycode == 115)
		data->keys.down = 0;
	if (keycode == 100)
		data->keys.right = 0;
	if (keycode == 97)
		data->keys.left = 0;
	return (0);
}

void	left_right(t_data *data, double *dx, double *dy, double rad)
{
	if (data->keys.left)
	{
		*dx += cos(rad - 3.14159265 / 2);
		*dy += sin(rad - 3.14159265 / 2);
	}
	if (data->keys.right)
	{
		*dx += cos(rad + 3.14159265 / 2) * 1;
		*dy += sin(rad + 3.14159265 / 2) * 1;
	}
	if (can_moove(data, *dx, *dy))
	{
		data->player->x += *dx;
		data->player->y += *dy;
	}
	render_frame(data);
}

int	loop_hook(t_data *data)
{
	double	rad;
	double	dx;
	double	dy;

	dx = 0;
	dy = 0;
	rad = data->player->r * 3.14159265 / 180.0;
	if (data->keys.view_left)
		data->player->r -= 2.5;
	if (data->keys.view_right)
		data->player->r += 2.5;
	if (data->keys.up)
	{
		dx += cos(rad);
		dy += sin(rad);
	}
	if (data->keys.down)
	{
		dx -= cos(rad);
		dy -= sin(rad);
	}
	left_right(data, &dx, &dy, rad);
	return (0);
}

int	close_hook(void *param)
{
	t_data	*data;

	data = param;
	exit_game(data);
	return (0);
}
