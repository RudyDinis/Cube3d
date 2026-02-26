/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   load_img.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:14:47 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/26 19:22:46 by rdinis           ###   ########.fr       */
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
	data->minimap->wall_we = mlx_xpm_file_to_image(data->mlx,
			data->data_map->we_texture, &img_width, &img_height);
	if (!data->minimap->wall_we)
		return (error_handler(data, 3), 1);
	data->minimap->wall_addr_we = mlx_get_data_addr(
			data->minimap->wall_we, &bits_per_pixel, &size_line, &endian);
	data->minimap->wall_bpp_we = bits_per_pixel;
	data->minimap->wall_size_line_we = size_line;
	return (0);
}

int	load_img3(t_data *data)
{
	int	img_width;
	int	img_height;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	data->minimap->wall_ea = mlx_xpm_file_to_image(data->mlx,
			data->data_map->ea_texture, &img_width, &img_height);
	if (!data->minimap->wall_ea)
		return (error_handler(data, 3), 1);
	data->minimap->wall_addr_ea = mlx_get_data_addr(
			data->minimap->wall_ea, &bits_per_pixel, &size_line, &endian);
	data->minimap->wall_bpp_ea = bits_per_pixel;
	data->minimap->wall_size_line_ea = size_line;
	data->minimap->wall_so = mlx_xpm_file_to_image(data->mlx,
			data->data_map->so_texture, &img_width, &img_height);
	if (!data->minimap->wall_so)
		return (error_handler(data, 3), 1);
	data->minimap->wall_addr_so = mlx_get_data_addr(
			data->minimap->wall_so, &bits_per_pixel, &size_line, &endian);
	data->minimap->wall_bpp_so = bits_per_pixel;
	data->minimap->wall_size_line_so = size_line;
	return (0);
}

int	load_img(t_data *data)
{
	int	img_width;
	int	img_height;
	int	bits_per_pixel;
	int	size_line;
	int	endian;

	data->minimap->wall_no = mlx_xpm_file_to_image(data->mlx,
			data->data_map->no_texture, &img_width, &img_height);
	if (!data->minimap->wall_no)
		return (error_handler(data, 3), 1);
	data->minimap->wall_addr_no = mlx_get_data_addr(
			data->minimap->wall_no, &bits_per_pixel, &size_line, &endian);
	data->minimap->wall_bpp_no = bits_per_pixel;
	data->minimap->wall_size_line_no = size_line;
	data->minimap->door_c = mlx_xpm_file_to_image(data->mlx,
			"./src/img/doorC.xpm", &img_width, &img_height);
	if (!data->minimap->door_c)
		return (error_handler(data, 3), 1);
	data->minimap->door_c_addr = mlx_get_data_addr(
			data->minimap->door_c, &bits_per_pixel, &size_line, &endian);
	data->minimap->door_c_bpp = bits_per_pixel;
	data->minimap->door_c_size_line = size_line;
	if (load_img2(data) == 1 || load_img3(data) == 1)
		return (1);
	return (0);
}
