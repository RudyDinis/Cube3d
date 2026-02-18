#include "parsing.h"

int check_xpm_size_settings_2(char **split, int i, char *ID)
{
	if (i != 4)
		return ft_printf_error(
				"Error\n%s: XPM file: wrong number of parameters (%d: expected 4)\n",
					ID, i), 1;
	if (ft_atoi(&split[0][1]) != 32)
		return ft_printf_error(
				"Error\n%s: XPM file: texture size not supported (%d: expected 32)\n",
					ID, ft_atoi(split[0])), 1;
	if (ft_atoi(split[1]) != 32)
		return ft_printf_error(
				"Error\n%s: XPM file: texture size not supported (%d: expected 32)\n",
					ID, ft_atoi(split[1])), 1;
	if (ft_atoi(split[2]) <= 0)
		return ft_printf_error(
				"Error\n%s: XPM file: incorrect number of color (%d: expected more than 0)\n",
					ID, ft_atoi(split[1])), 1;
	if (ft_atoi(split[3]) != 1)
		return ft_printf_error(
				"Error\n%s: XPM file: number of character per pixel not supported (%d: expected 1)\n",
					ID, ft_atoi(split[3])), 1;
	return 0;
}

int check_xpm_size_settings(char *line, char *ID)
{
	char **split;
	int i;
	int y;

	split = ft_split(line, " \t\n");
	i = 0;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (i == 0 && split[0][0] == '\"')
			{
				y++;
				continue ;
			}
			if (!split[i + 1] && split[i][y] == '\"' && split[i][y + 1] && split[i][y + 1] == ',' && !split[i][y + 2])
				break ;
			if (!ft_isdigit(split[i][y]))
				return ft_printf_error(
					"Error\n%s: XPM file: numeric arguments required \n", ID), 1;
			y++;
		}
		i++;
	}
	return (check_xpm_size_settings_2(split, i, ID));
}

int check_xpm(char *texture, char *ID)
{
	int fd;
	char *line;
	long count;

	count = 0;
	fd = open(texture, O_RDONLY);
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
		if (!line)
			break ;
		if (line && *line != '\n' && count == 1)
		{
			if (check_xpm_size_settings(line, ID) == 1)
				return (free(line), 1);
			break ;
		}
		free(line);
		line = get_next_line(fd, 0);
		count++;
	}
	if (line)
		free(line);
	return (0);
}
