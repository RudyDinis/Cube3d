/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mouse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/23 15:50:30 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/23 15:52:35 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	mouse_move_hook(int x, int y, void *param)
{
	t_data	*data;
	int		dx;

	(void)y;
	data = param;
	dx = x - 960;
	data->player->r += dx * 0.3;
	mlx_mouse_move(data->mlx, data->mlx_win, 1920 / 2, 1080 / 2);
	return (0);
}
