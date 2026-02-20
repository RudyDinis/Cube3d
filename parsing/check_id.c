#include "parsing.h"

int check_ID_order(char **split, t_id *id, int pos)
{
	int i;
	int j;

	j = 0;
	i = 0;
	while (id->done[i])
	{
		if (!ft_findstr(*split, id->done[i]))
			return (ft_printf_error("Error\n%s: duplicate\n", *split),
					free_everything((void **)split), 2);
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

int check_ID_other(char *line,char *ID)
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
	split_color = ft_split(split[1], ",");
	if (!split_color)
		return (free_everything((void **)split), 1);
	if (check_ID_other_color(split, ID, split_color))
		return (1);
	return (0);
}

int check_ID_cardinal(char *line, int pos, char *ID, t_id *id)
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
	if	(check_ID_order(split, id, pos) == 2)
		return (2);
	if (!ft_findstr(*split, "F") || !ft_findstr(*split, "C"))
	{
		free(split);
		return check_ID_other(line, ID);
	}
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

int check_identifier(int fd, t_id *id)
{
	char *line;
	int i;
	i = 0;

	line = get_next_line(fd, 0);
	while (line)
	{
		while (*line == '\n')
		{
			free(line);
			line = get_next_line(fd, 0);
			if (!line)
				break ;
		}
		if (check_ID_cardinal(line, i, "jsp", id))
			return 1;
		free(line);
		line = get_next_line(fd, 0);
		i++;
	}
	if (i != 6)
		return (ft_printf_error("Error\nWrong number of identifier\n"), 1);
	return 0;
}
