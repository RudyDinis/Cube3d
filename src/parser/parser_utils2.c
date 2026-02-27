/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils2.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/27 11:14:27 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/27 11:15:00 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

void	free_id(t_id *id, int param)
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
	if (id->data && param)
		free_data(id->data);
	if (id)
		free(id);
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
