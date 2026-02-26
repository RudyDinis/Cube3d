/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_len.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/26 14:46:47 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/26 14:56:50 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	get_height(char **map)
{
	int	y;

	y = 0;
	while (map[y])
		y++;
	return (y);
}

int	get_width(char **map)
{
	int	x;
	int	y;
	int	x_max;

	y = 0;
	x_max = 0;
	while (map[y])
	{
		x = 0;
		while (map[y][x])
			x++;
		if (x > x_max)
			x_max = x;
		y++;
	}
	return (x_max);
}
