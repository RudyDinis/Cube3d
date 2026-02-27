/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moove.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 14:24:59 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/27 10:35:18 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	can_moove(t_data *data, double dx, double dy)
{
	if (data->map->map[(int)(data->player->y + dy) / 32]
		[(int)(data->player->x + dx) / 32] == '1')
		return (0);
	if (data->map->map[(int)(data->player->y + dy) / 32]
		[(int)(data->player->x + dx) / 32] == '5')
		return (0);
	else if (data->map->map[(int)(data->player->y + dy) / 32]
		[(int)(data->player->x + dx) / 32] == 'P')
		return (0);
	return (1);
}
