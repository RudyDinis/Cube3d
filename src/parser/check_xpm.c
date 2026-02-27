/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_xpm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/24 14:03:13 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/27 13:07:03 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/cube3d.h"

int	check_xpm_size_settings_2(char *line, char **split, int i)
{
	if (i != 4)
		return (ft_printf_error(
				"Error\n%s: %s (%d: expected 4)\n",
				line, XPM_PARAM), free_vector(split), 1);
	if (ft_atoi(&split[0][1]) != 32)
		return (ft_printf_error(
				"Error\n%s: %s (%d: expected 32)\n",
				line, XPM_TEXTURE, ft_atoi(split[0])), free_vector(split), 1);
	if (ft_atoi(split[1]) != 32)
		return (ft_printf_error(
				"Error\n%s: %s (%d: expected 32)\n",
				line, XPM_TEXTURE, ft_atoi(split[1])), free_vector(split), 1);
	if (ft_atoi(split[2]) <= 0)
		return (ft_printf_error(
				"Error\n%s: %s (%d: expected more than 0)\n",
				line, XPM_COLOR, ft_atoi(split[1])), free_vector(split), 1);
	if (ft_atoi(split[3]) != 1 && ft_atoi(split[3]) != 2)
		return (ft_printf_error(
				"Error\n%s: %s (%d: expected 1)\n",
				line, XPM_PIXEL, ft_atoi(split[3])), free_vector(split), 1);
	return (free_vector(split), 0);
}

int	check_xpm_return(char *line, char **s)
{
	return (ft_printf_error("Error\n%s: %s\n", line, XPM_NUM), free_vector(s), 1);
}

int	check_xpm_size_settings(char *line)
{
	int (y);
	int (i) = 0;
	char **(s) = ft_split(line, " \t\n");
	if (!s)
		return (1);
	while (s[i])
	{
		y = 0;
		while (s[i][y])
		{
			if (i == 0 && s[0][0] == '\"')
			{
				y++;
				continue ;
			}
			if (s[i][y] && !s[i + 1] && s[i][y] == '\"'
				&& s[i][y + 1] && s[i][y + 1] == ',' && !s[i][y + 2])
				break ;
			if (s[i][y] && !ft_isdigit(s[i][y]))
				return (check_xpm_return(line, s));
			y++;
		}
		i++;
	}
	return (check_xpm_size_settings_2(line, s, i));
}

int	check_xpm(char *texture)
{
	int		fd;
	char	*line;
	long	count;

	count = 0;
	fd = open(texture, O_RDONLY);
	line = get_next_line(fd, 0);
	while (line)
	{
		skip_newline(&line, fd);
		if (!line)
			break ;
		if (line && *line != '\n' && count == 1)
		{
			if (check_xpm_size_settings(line) == 1)
				return (free(line), get_next_line(fd, 2), 1);
			break ;
		}
		free(line);
		line = get_next_line(fd, 0);
		count++;
	}
	if (line)
		free(line);
	return (get_next_line(fd, 2), 0);
}
