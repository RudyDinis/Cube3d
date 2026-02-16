#include "../libft/libft.h"

//TODO faire gaffe à ne pas accepter les directories

int check_map_extension(char *path)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (i >= 5)
	{
		if (!ft_findstr(&path[i - 5], ".cub"))
			return 1;
	}
	return 0;
}

int check_xpm_size(char *line, int color_nb)
{
	char **split;
	int i;
	int y;

	split = ft_split(line, ' ,\t\"');
	//TODO quand tu split, tu récupères littéralement '"32 32 5 1",'
	i = 0;
	while (split[i])
	{
		y = 0;
		while (split[i][y])
		{
			if (!ft_isdigit(split[i][y]))
				return 1;
			y++;
		}
		i++;
	}
	if (i < 4)
		return 1;
	i = 0;
	if (ft_atoi(split[0] != 32)
		return 1;
	color_nb = ft_atoi(split[1]);
	if (ft_atoi(split[1] != 32)
		return 1;
	if (ft_atoi(split[3]) != 1)
		return 1;
}

int check_xpm(char *texture)
{
	//TODO CHECK LA SIZE
	//TODO CHECK LA TAILLE DE CHAQUE LIGNE
	int fd;
	char *line;
	long count;
	int valid;

	valid = 0;
	count = 0;
	fd = open(texture, O_RDONLY);
	line = get_next_line(fd, 0);
	while (gnl)
	{
		while (*line == '\n')
		{
			free(line);
			line = get_next_line(fd, 0);
			if (!line)
				break ;
		}

		free(line);
		line = get_next_line(fd, 0);
		if (count == 1)
		count++;
	}

	while ()
}

int check_NO(char *line)
{
	char **split;
	int i;
	int fd;

	i = 0;
	split = ft_split(line, ' ');
	if (!split)
		return 1;
	while (split[i])
		i++;
	if (i != 2)
		return (ft_printf_error("Error\nNorth texture: syntax error\n"),
			free_everything(split), 2);
	if (!ft_findstr(*split, "NO"))
		return (ft_printf_error("Error\nNorth texture: wrong identifier\n"),
			free_everything(split), 2);
	if (ft_strlen(split[1] < 4))
		return (ft_printf_error("Error\nNorth texture: path error\n"),
			free_everything(split), 2);
	if (ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".xpm")
		&& ft_findstr(&split[1][ft_strlen(split[1]) - 4], ".png"))
		return (ft_printf_error("Error\nNorth texture: wrong file extension\n"),
			free_everything(split), 2);
	fd = open(split[1]);
	if (fd < 0)
		return (ft_printf("Error\nNorth texture: texture not found\n"), 2);
	close(fd);
	return 0;
}

void check_identifier(int map)
{
	char *gnl;
	int i;
	i = 0;

	gnl = get_next_line(fd, 0);
	while (gnl)
	{
		while (*gnl ==  '\n')
		{
			free(gnl);
			gnl = get_next_line(fd, 0);
		}
		if (i == 0)
			check
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
}

void check_map(char *map)
{
	int fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_error("Error\n%s: Map not found", map);
		exit(1);
	}

}
