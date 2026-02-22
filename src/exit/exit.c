/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:15:38 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/22 19:41:33 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_map(char **map, int height)
{
	int	y;

	y = 0;
	while (y < height)
		free(map[y++]);
	free(map);
}

void	exit2(t_data *data)
{
	if (data->player)
	{
		if (data->player->data_img.img)
			mlx_destroy_image(data->mlx, data->player->data_img.img);
		free(data->player);
	}
	if (data->minimap)
		free(data->minimap);
	if (data->vision.img)
		mlx_destroy_image(data->mlx, data->vision.img);
}

void	exit_game(t_data *data)
{
	if (!data)
		return ;
	if (data->mlx_win)
		mlx_destroy_window(data->mlx, data->mlx_win);
	if (data->minimap->door)
		mlx_destroy_image(data->mlx, data->minimap->door);
	if (data->minimap->wall)
		mlx_destroy_image(data->mlx, data->minimap->wall);
	exit2(data);
	if (data->mlx)
	{
		mlx_loop_end(data->mlx);
		mlx_destroy_display(data->mlx);
		free(data->mlx);
	}
	if (data->map)
	{
		free_map(data->map->map, data->map->height);
		free(data->map);
	}
	free(data);
	exit(1);
}
