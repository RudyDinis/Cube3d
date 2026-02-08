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

int load_img(t_data *data)
{
    int img_width;
    int img_height;
    int bits_per_pixel;
    int size_line;
    int endian;

    data->minimap->wall = mlx_xpm_file_to_image(data->mlx,
            "./src/img/wall.xpm", &img_width, &img_height);
    if (!data->minimap->wall)
        return (1);
    data->minimap->wall_addr = mlx_get_data_addr(
        data->minimap->wall,  &bits_per_pixel, &size_line, &endian
    );
	data->minimap->wall_bpp = bits_per_pixel;
	data->minimap->wall_size_line = size_line;
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




	data->map->width = 20;
	data->map->height = 10;

	srand(time(NULL));
	data->map->map = generate_map(data->map->width, data->map->height);
	print_map(data->map->map, data->map->height);





	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1920, 1080, "Hello word!");
	data->vision.img = mlx_new_image(data->mlx, 1920, 1080);
	data->vision.addr = mlx_get_data_addr(data->vision.img, &data->vision.bits_per_pixel, &data->vision.line_length, &data->vision.endian);
	if (load_img(data) == 1)
		return (1);
	init_player(data);
	raycasting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->vision.img, 0, 0);
	draw_player_arrow(data, 0);
	load_minimap(data);
	mlx_hook(data->mlx_win, 2, 1L << 0, key_press, data);
	mlx_hook(data->mlx_win, 3, 1L << 1, key_release, data);
	mlx_loop_hook(data->mlx, loop_hook, data);
	mlx_hook(data->mlx_win, 17, 0, close_hook, data);
	mlx_loop(data->mlx);
	return (0);
}
