/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:06:10 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/26 14:23:33 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

// TODO faire gaffe à ne pas accepter les directories

int	closed_condition(char **s, int i, size_t y)
{
	if (i == 0 || !s[i + 1])
	{
		ft_printf_error("Error\nInvalid map: not closed\n");
		return (1);
	}
	else if (y == 0 || !s[i][y + 1])
	{
		ft_printf_error("Error\nInvalid map: not closed\n");
		return (1);
	}
	else if (y >= ft_strlen(s[i - 1]) || y >= ft_strlen(s[i + 1])
		|| s[i][y + 1] == '5' || s[i][y - 1] == '5'
		|| s[i + 1][y] == '5' || s[i - 1][y] == '5')
	{
		ft_printf_error("Error\nInvalid map: not closed\n");
		return (1);
	}
	return (0);
}

int	check_coponents(char **split)
{
	int	i;
	int	y;
	int	spawn;

	i = 0;
	spawn = 0;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (split[i][y] == 'N' || split[i][y] == 'W'
				|| split[i][y] == 'S' || split[i][y] == 'E')
				spawn++;
			y++;
		}
		i++;
	}
	free_vector(split);
	if (spawn != 1)
		return (ft_printf_error("Error\nRequirements not fulfilled\n"), 1);
	return (0);
}

int	check_space(char **split)
{
	int	i;
	int	y;

	i = 0;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (split[i][y] == '0' || split[i][y] == 'N' || split[i][y] == 'W'
				|| split[i][y] == 'S' || split[i][y] == 'E')
				return (check_coponents(split));
			y++;
		}
		i++;
	}
	ft_printf_error("Error\nRequirements not fulfilled\n");
	free_vector(split);
	return (1);
}

int	check_closed(char *map)
{
	char	**s;
	size_t	y;

	int (i) = 0;
	s = ft_split(map, "\n");
	if (!s)
		return (1);
	while (s[i])
	{
		y = 0;
		while (s[i][y])
		{
			if (s[i][y] == '0' || s[i][y] == 'P' || s[i][y] == 'p'
				|| s[i][y] == 'N' || s[i][y] == 'W' || s[i][y] == 'S'
				|| s[i][y] == 'E')
				if (closed_condition(s, i, y))
					return (free_vector(s), 1);
			if (!check_valid_char(s[i][y]))
				return (free_vector(s), 1);
			y++;
		}
		i++;
	}
	return (check_space(s));
}

t_map_data	*check_map(char *map)
{
	int			fd;
	char		*copy;
	t_id		*id;
	t_map_data	*map_data;

	fd = open(map, O_RDONLY);
	if (fd < 0)
		return (ft_printf_error("Error\n%s: map not found\n", map), NULL);
	if (!check_map_extension(map))
		return (ft_printf_error("Error\n%s: wrong file extension\n", map), NULL);
	id = malloc_id();
	if (!id)
		return (NULL);
	check_identifier(fd, id);
	free_id(id, 1);
	id = malloc_id();
	if (!id)
		return (NULL);
	copy = fill_map(fd, map, id);
	if (!copy || (copy && check_closed(copy)))
		return (free_id(id, 1), free(copy), NULL);
	id->data->map = ft_split(copy, "\n");
	if (!id->data->map)
		return (free_id(id, 1), free(copy), NULL);
	return (map_data = id->data, free(copy), free_id(id, 0), map_data);
}
