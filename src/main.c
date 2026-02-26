/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:18:07 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/26 12:25:20 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

void	load_minimap(t_data *data)
{
	int	y;
	int	x;

	y = 0;
	while (y < data->map->height && data->map->map[y])
	{
		x = 0;
		while (data->map->map[y][x])
		{
			if (data->map->map[y][x] == '1')
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->minimap->wall, x * 32, y * 32);
			if (data->map->map[y][x] == 'P')
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->minimap->door_c, x * 32, y * 32);
			x++;
		}
		y++;
	}
}

int	init(t_data *data)
{
	data->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!data->minimap)
		return (error_handler(data, 0), 1);
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return (error_handler(data, 1), 1);
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (error_handler(data, 2), 1);
	return (0);
}

int	main(int argc, char **argv)
{
	t_data	*data;

	if (argc != 2)
		return (1);
	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	if (init(data) == 1)
		return (1);
	check_map(argv[1], data->data_map);
	printf("%s\n", data->data_map->no_texture);
	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Cub3d");
	data->vision.img = mlx_new_image(data->mlx, 1920, 1080);
	data->vision.addr = mlx_get_data_addr(data->vision.img,
			&data->vision.bits_per_pixel, &data->vision.line_length,
			&data->vision.endian);
	if (load_img(data) == 1)
		return (1);
	init_player(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->vision.img, 0, 0);
	draw_player_arrow(data, 0);
	load_minimap(data);
	mlx_mouse_hide(data->mlx, data->mlx_win);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->mlx_win, 17, 0, close_hook, data);
	mlx_mouse_move(data->mlx, data->mlx_win, 1920 / 2, 1080 / 2);
	mlx_hook(data->mlx_win, 6, 1L << 6, mouse_move_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
