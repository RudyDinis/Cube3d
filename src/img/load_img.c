/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:14:47 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/24 14:14:17 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	load_img2(t_data *data)
{
	int	img_width;
	int	img_height;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	data->minimap->door_o = mlx_xpm_file_to_image(data->mlx,
			"./src/img/doorO.xpm", &img_width, &img_height);
	if (!data->minimap->door_o)
		return (error_handler(data, 3), 1);
	data->minimap->door_o_addr = mlx_get_data_addr(
			data->minimap->door_o, &bits_per_pixel, &size_line, &endian);
	data->minimap->door_o_bpp = bits_per_pixel;
	data->minimap->door_o_size_line = size_line;
	return (0);
}

int	load_img(t_data *data)
{
	int	img_width;
	int	img_height;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	data->minimap->wall = mlx_xpm_file_to_image(data->mlx,
			"./src/img/wall.xpm", &img_width, &img_height);
	if (!data->minimap->wall)
		return (error_handler(data, 3), 1);
	data->minimap->wall_addr = mlx_get_data_addr(
			data->minimap->wall, &bits_per_pixel, &size_line, &endian);
	data->minimap->wall_bpp = bits_per_pixel;
	data->minimap->wall_size_line = size_line;
	data->minimap->door_c = mlx_xpm_file_to_image(data->mlx,
			"./src/img/doorC.xpm", &img_width, &img_height);
	if (!data->minimap->door_c)
		return (error_handler(data, 3), 1);
	data->minimap->door_c_addr = mlx_get_data_addr(
			data->minimap->door_c, &bits_per_pixel, &size_line, &endian);
	data->minimap->door_c_bpp = bits_per_pixel;
	data->minimap->door_c_size_line = size_line;
	if (load_img2(data) == 1)
		return (1);
	return (0);
}
