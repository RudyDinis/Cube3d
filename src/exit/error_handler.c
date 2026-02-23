/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/22 19:47:45 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/23 19:06:57 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	img_error(t_data *data)
{
	exit_game(data);
}

void	*error_handler(t_data *data, int id)
{
	if (id == 0)
		return (free(data), printf(RED MALLOC_ERR RESET), NULL);
	if (id == 1)
		return (free(data->minimap), free(data),
			printf(RED MALLOC_ERR RESET), NULL);
	if (id == 2)
		return (free(data->minimap), free(data->map),
			printf(RED MALLOC_ERR RESET), free(data), NULL);
	if (id == 3)
		return (printf(RED IMG_ERR RESET), img_error(data), NULL);
	if (id == 4)
		return (free(data->minimap), free(data->map), free(data->player),
			printf(RED MALLOC_ERR RESET), free(data), NULL);
	return (NULL);
}
