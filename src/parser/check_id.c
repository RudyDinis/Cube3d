/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*  id.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:06:23 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/24 14:49:09 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	copy_content(int pos, t_id *id, char *texture, char **color)
{
	if (!ft_findstr(id->done[pos], "NO"))
		id->data->no_texture = ft_strdup(texture);
	if (!ft_findstr(id->done[pos], "SO"))
		id->data->so_texture = ft_strdup(texture);
	if (!ft_findstr(id->done[pos], "EA"))
		id->data->ea_texture = ft_strdup(texture);
	if (!ft_findstr(id->done[pos], "WE"))
		id->data->we_texture = ft_strdup(texture);
	if (!ft_findstr(id->done[pos], "F"))
	{
		id->data->f_color[0] = ft_strdup(color[0]);
		id->data->f_color[1] = ft_strdup(color[1]);
		id->data->f_color[2] = ft_strdup(color[2]);
	}
	if (!ft_findstr(id->done[pos], "C"))
	{
		id->data->c_color[0] = ft_strdup(color[0]);
		id->data->c_color[1] = ft_strdup(color[1]);
		id->data->c_color[2] = ft_strdup(color[2]);
	}
}

int	check_id_other_color(char **s, char **s_col, t_id *id, int pos)
{
	int	j;

	int (k) = 0;
	while (s_col[k])
	{
		j = 0;
		while (s_col[k][j])
		{
			if (!ft_isdigit(s_col[k][j]))
				return (ft_printf_error(
						"Error\n%s: numeric arguments required \n", s[0]),
					free_vector(s), free_vector(s_col), 1);
			j++;
		}
		if (ft_atoi(s_col[k]) < 0 || ft_atoi(s_col[k]) > 255)
			return (ft_printf_error(
					"Error\n%s: color value between 0 and 255 required \n", s[0]),
				free_vector(s), free_vector(s_col), 1);
		k++;
	}
	if (k != 3)
		return (free_vector(s_col),
			ft_printf_error("Error\n%s: wrong number of arguments (expected 3)\n"
				, s, k), free_vector(s), 1);
	return (copy_content(pos, id, NULL, s_col), 0);
}

int	check_id_other(char *line, t_id *id, int pos)
{
	int		i;
	int		k;
	char	**split_color;
	char	**split;

	split = ft_split(line, " \t\n");
	i = 0;
	k = 0;
	if (!split)
		return (1);
	while (split[i])
		i++;
	if (i != 2)
		return (ft_printf_error("Error\n%s: syntax error\n", line),
			free_vector(split), 2);
	split_color = ft_split(split[1], ",");
	if (!split_color)
		return (free_vector(split), 1);
	if (check_id_other_color(split, split_color, id, pos))
		return (1);
	free_vector(split);
	free_vector(split_color);
	return (0);
}

int	check_id_cardinal_2(char **split, int fd, t_id *id, int pos)
{
	if (ft_strlen(split[1]) >= 4
		&& ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".xpm"))
		return (ft_printf_error(
				"Error\n%s: wrong file extension (.xpm accepted)\n",
				split[1]), free_vector(split), 2);
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		return (ft_printf("Error\n%s: texture not found\n", split[1]),
			free_vector(split), 2);
	close(fd);
	if (!ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".xpm"))
	{
		if (check_xpm(split[1]))
			return (free_vector(split), 2);
	}
	copy_content(pos, id, split[1], NULL);
	free_vector(split);
	return (0);
}

int	check_id_cardinal(char *line, int *pos, t_id *id)
{
	int		i;
	int		fd;
	char	**split;

	i = 0;
	split = ft_split(line, " \t\n");
	if (!split)
		return (1);
	while (split[i])
		i++;
	if (i != 2)
		return (ft_printf_error("Error\n%s: syntax error\n", split[0]),
			free_vector(split), 2);
	if (ft_strlen(split[1]) < 4)
		return (ft_printf_error("Error\n%s: path error\n", split[1]),
			free_vector(split), 2);
	if (check_id_order(split, id, *pos) == 2)
		return (free_vector(split), 2);
	(*pos)++;
	if (!ft_findstr(*split, "F") || !ft_findstr(*split, "C"))
		return (free_vector(split), check_id_other(line, id, (*pos) - 1));
	return (fd = 0, check_id_cardinal_2(split, fd, id, (*pos) - 1));
}

void	check_identifier(int fd, t_id *id)
{
	int		i;
	char	*line;

	i = 0;
	line = get_next_line(fd, 0);
	while (line && i < 6)
	{
		while (*line == '\n')
		{
			free(line);
			line = get_next_line(fd, 0);
			if (!line)
				break ;
		}
		if (check_id_cardinal(line, &i, id))
			return (free(line), get_next_line(fd, 2), free_id(id, 1), exit(1));
		free(line);
		line = get_next_line(fd, 0);
	}
	if (line)
		free(line);
	if (i != 6)
		return (ft_printf_error("Error\nWrong number of identifier\n"),
			free_id(id, 1), close(fd), exit(1));
}
