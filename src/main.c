/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:18:07 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/07 19:35:43 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/cube3d.h"

int	load_img(t_data *data)
{
	int	img_width;
	int	img_height;

	data->minimap->wall = mlx_xpm_file_to_image(data->mlx,
			"./src/img/wall.xpm", &img_width, &img_height);
	if (!data->minimap->wall)
		return (1);
	data->minimap->ground = mlx_xpm_file_to_image(data->mlx,
			"./src/img/ground.xpm", &img_width, &img_height);
	if (!data->minimap->ground)
		return (1);
	return (0);
}

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
			{
				mlx_put_image_to_window(data->mlx, data->mlx_win,
					data->minimap->wall, x * 32, y * 32);
			}
			x++;
		}
		y++;
	}
}

int	init(t_data *data)
{
	data->minimap = ft_calloc(1, sizeof(t_minimap));
	if (!data->minimap)
		return (1);
	data->map = ft_calloc(1, sizeof(t_map));
	if (!data->map)
		return (1);
	data->player = ft_calloc(1, sizeof(t_player));
	if (!data->player)
		return (1);
	return (0);
}

int	main(void)
{
	t_data	*data;

	data = ft_calloc(1, sizeof(t_data));
	if (!data)
		return (1);
	if (init(data) == 1)
		return (1);




	data->map->width = 10;
	data->map->height = 5;

	srand(time(NULL));
	data->map->map = generate_map(data->map->width, data->map->height);
	print_map(data->map->map, data->map->height);





	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Hello word!");
	if (load_img(data) == 1)
		return (1);
	load_minimap(data);
	init_player(data);
	mlx_loop(data->mlx);
	return (0);
}
