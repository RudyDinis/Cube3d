/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checker.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:04:41 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/25 19:58:52 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_valid_char(char c)
{
	if (c == '0' || c == 'P' || c == 'p'
		|| c == 'N' || c == 'W' || c == 'S'
		|| c == 'E' || c == '1' || c == '5')
		return (1);
	ft_printf_error("Error\nMap contains unsupported characters\n");
	return (0);
}

int	check_id_order(char **split, t_id *id, int pos)
{
	int	i;
	int	j;

	j = 0;
	i = 0;
	while (id->done[i])
	{
		if (!ft_findstr(*split, id->done[i]))
			return (ft_printf_error("Error\n%s: duplicate\n", *split),
				free_vector(split), 2);
		i++;
	}
	while (id->id[j])
	{
		if (!ft_findstr(*split, id->id[j]))
		{
			id->done[pos] = ft_strdup(*split);
			return (0);
		}
		j++;
	}
	ft_printf_error("Error\n%s: wrong identifier\n", *split);
	return (2);
}

int	check_map_extension(char *path)
{
	int	i;

	i = 0;
	while (path[i])
		i++;
	if (i >= 5)
	{
		if (!ft_findstr(&path[i - 4], ".cub"))
			return (1);
	}
	return (0);
}

size_t	get_map_size(int fd, t_id *id)
{
	char	*map;
	size_t	len;

	len = 0;
	map = get_next_line(fd, 0);
	while (map && *map == '\n')
	{
		free(map);
		map = get_next_line(fd, 0);
	}
	while (map)
	{
		len += ft_strlen(map);
		if (len > 100000)
		{
			ft_printf_error("Error\nMap length exceeded 100k characters\n");
			return (free(map), free_id(id), get_next_line(fd, 2), exit(1), 1);
		}
		free(map);
		map = get_next_line(fd, 0);
	}
	close(fd);
	return (len);
}

t_map_data	*malloc_data(void)
{
	t_map_data	*data;

	data = ft_calloc(1, sizeof(t_map_data));
	if (!data)
		return (NULL);
	data->c_color = ft_calloc(3 + 1, sizeof(char *));
	if (!data->c_color)
		return (free(data), NULL);
	data->f_color = ft_calloc(3 + 1, sizeof(char *));
	if (!data->f_color)
		return (free_vector(data->c_color), free(data), NULL);
	return (data);
}