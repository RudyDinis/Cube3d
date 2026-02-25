/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 10:51:47 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/25 19:50:44 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

char	*fill_map(int fd, char *map, t_id *id)
{
	char	*gnl;
	size_t	size;

	size_t (j) = 0;
	size_t (i) = 0;
	size = get_map_size(fd, id);
	if (!size)
		return (get_next_line(fd, 2), ft_printf_error("Error\nMap is empty\n"),
			NULL);
	fd = open(map, O_RDONLY);
	check_identifier(fd, id);
	char *(copy) = ft_calloc(size + 1, 1);
	if (!copy)
		return (NULL);
	gnl = get_next_line(fd, 0);
	skip_newline(&gnl, fd);
	while (gnl)
	{
		ft_memcpy(&copy[i], gnl, ft_strlen(gnl));
		i += ft_strlen(gnl);
		replace_space(copy, &j, i);
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	return (get_next_line(fd, 2), copy);
}

t_id	*malloc_id(t_map_data *data)
{
	t_id	*id;
	int		i;

	i = 0;
	id = ft_calloc(1, sizeof(t_id));
	if (!id)
		return (NULL);
	id->id = ft_calloc(6 + 1, sizeof(char *));
	if (!id->id)
		return (free(id), NULL);
	id->id[0] = ft_strdup("NO");
	id->id[1] = ft_strdup("SO");
	id->id[2] = ft_strdup("EA");
	id->id[3] = ft_strdup("WE");
	id->id[4] = ft_strdup("F");
	id->id[5] = ft_strdup("C");
	id->done = ft_calloc(6 + 1, sizeof(char *));
	if (!id->done)
		return (id->done = NULL, free_id(id), NULL);
	id->data = data;
	return (id);
}

void	skip_newline(char **line, int fd)
{
	while (*line && **line == '\n')
	{
		free(*line);
		*line = get_next_line(fd, 0);
		if (!(*line))
			break ;
	}
}

void	replace_space(char *copy, size_t *j, size_t i)
{
	while (*j < i && copy[*j])
	{
		if (copy[*j] == ' ')
			copy[*j] = '5';
		(*j)++;
	}
}
void	free_data(t_map_data *data)
{
	if (!data)
		return ;
	if (data->no_texture)
		free(data->no_texture);
	if (data->so_texture)
		free(data->so_texture);
	if (data->we_texture)
		free(data->we_texture);
	if (data->ea_texture)
		free(data->ea_texture);
	free_vector(data->c_color);
	free_vector(data->f_color);
	free(data);
}

void	free_id(t_id *id)
{
	int	i;

	i = 0;
	while (i < 6)
	{
		if (id->id)
			free(id->id[i]);
		if (id->done && id->done[i])
			free(id->done[i]);
		i++;
	}
	if (id->id)
		free(id->id);
	if (id->done)
		free(id->done);
	if (id->data)
		free_data(id->data);
	if (id)
		free(id);
}