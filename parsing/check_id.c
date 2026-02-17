#include "parsing.h"

int check_ID_order(char **split, int pos)
{
	if (pos == 0)
		if (ft_findstr(*split, "NO"))
				return (ft_printf_error("Error\nNorth texture: wrong identifier\n"),
					free_everything((void **)split), 2);
	if (pos == 1)
		if (ft_findstr(*split, "SO"))
				return (ft_printf_error("Error\nSouth texture: wrong identifier\n"),
					free_everything((void **)split), 2);
	if (pos == 2)
		if (ft_findstr(*split, "WE"))
				return (ft_printf_error("Error\nWest texture: wrong identifier\n"),
					free_everything((void **)split), 2);
	if (pos == 3)
		if (ft_findstr(*split, "EA"))
				return (ft_printf_error("Error\nEast texture: wrong identifier\n"),
					free_everything((void **)split), 2);
	if (pos == 4 && ft_findstr(*split, "F"))
		return (ft_printf_error("Error\n%Floor: wrong identifier\n"),
			free_everything((void **)split), 2);
	if (pos == 5 && ft_findstr(*split, "C"))
		return (ft_printf_error("Error\nCeiling: wrong identifier\n"),
			free_everything((void **)split), 2);
	return (0);
}

int check_ID_cardinal(char *line, int pos, char *ID)
{
	char **split;
	int i;
	int fd;

	i = 0;
	split = ft_split(line, " \t\n");
	if (!split)
		return 1;
	while (split[i])
		i++;
	if (i != 2)
		return (ft_printf_error("Error\n%s: syntax error\n", ID),
			free_everything((void **)split), 2);
	if (ft_strlen(split[1]) < 4)
		return (ft_printf_error("Error\n%s: path error\n", ID),
			free_everything((void **)split), 2);
	if	(check_ID_order(split, pos) == 2)
		return (2);
	if (ft_strlen(split[1]) >= 4 && ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".xpm")
		&& ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".png"))
		return (ft_printf_error("Error\n%s: wrong file extension (.xpm or .png accepted)\n", ID),
			free_everything((void **)split), 2);
	fd = open(split[1], O_RDONLY);
	if (fd < 0)
		return (free_everything((void **)split), ft_printf("Error\n%s: texture not found\n", ID), 2);
	close(fd);
	if (!ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".xpm"))
	{
		if (check_xpm(split[1], ID))
			return (free_everything((void **)split), 2);
	}
	return (free_everything((void **)split), 0);
}

int check_ID_other_color(char **split, char *ID, char **split_color)
{
	int k;
	int j;

	k = 0;
	while (split_color[k])
	{
		j = 0;
		while (split_color[k][j])
		{
			if (!ft_isdigit(split_color[k][j]))
				return (free_everything((void **)split), free_everything((void **)split_color),
					ft_printf_error(
					"Error\n%s: numeric arguments required \n", ID), 1);
			j++;
		}
		if (ft_atoi(split_color[k]) < 0 || ft_atoi(split_color[k]) > 255)
			return (free_everything((void **)split), free_everything((void **)split_color),
					ft_printf_error(
					"Error\n%s: color value between 0 and 255 required \n", ID), 1);
		k++;
	}
	if (k != 3)
		return (free_everything((void **)split), free_everything((void **)split_color),
			ft_printf_error("Error\n%s: wrong number of arguments (%d: expected 3)\n", ID, k), 1);
	return 0;
}

int check_ID_other(char *line, int pos, char *ID)
{
	char **split_color;
	char **split;
	int i;
	int k;

	split = ft_split(line, " \t\n");
	i = 0;
	k = 0;
	if (!split)
		return 1;
	while (split[i])
		i++;
	if (i != 2)
		return (ft_printf_error("Error\n%s: syntax error\n", ID),
			free_everything((void **)split), 2);
	if (check_ID_order(split, pos))
		return (1);
	split_color = ft_split(split[1], ",");
	if (!split_color)
		return (free_everything((void **)split), 1);
	if (check_ID_other_color(split, ID, split_color))
		return (1);
	return (0);
}

int check_identifier_2(char *line, int i)
{
		if (i == 0)
			if (check_ID_cardinal(line, i, "North texture"))
				return (free(line), 1);
		if (i == 1)
			if (check_ID_cardinal(line, i, "South texture"))
				return (free(line), 1);
		if (i == 2)
			if (check_ID_cardinal(line, i, "West texture"))
				return (free(line), 1);
		if (i == 3)
			if (check_ID_cardinal(line, i, "East texture"))
				return (free(line), 1);
		if (i == 4)
			if (check_ID_other(line, i, "Floor"))
				return (free(line), 1);
		if (i == 5)
			if (check_ID_other(line, i, "Ceiling"))
				return (free(line), 1);
		return (0);
}

int check_identifier(int fd)
{
	char *line;
	int i;
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
		if (check_identifier_2(line, i))
			return 1;
		free(line);
		line = get_next_line(fd, 0);
		i++;
	}
	if (i != 6)
		return (ft_printf_error("Error\nWrong number of identifier\n"), 1);
	return 0;
}
