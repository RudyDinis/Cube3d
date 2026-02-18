#include "parsing.h"

//TODO faire gaffe à ne pas accepter les directories

typedef struct s_xpm_data
{
	char **textures;
	int number_of_color;
}	t_xpm_data;

int check_map_extension(char *path)
{
	int i;

	i = 0;
	while (path[i])
		i++;
	if (i >= 5)
	{
		if (!ft_findstr(&path[i - 4], ".cub"))
			return 1;
	}
	return 0;
}

size_t get_map_size(int fd)
{
	char *map;
	size_t len;

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
		if (len > INT_MAX) //TODO PRINT UN MESSAGE DERREUR
			return (free(map), get_next_line(fd, 1), exit(1), 1);
		free(map);
		map = get_next_line(fd, 0);
	}
	close(fd);
	return len;
}

char *fill_map(int fd, char *map)
{
	char *map;
	size_t size;
	fd = open(map, O_RDONLY);
}

void check_map(char *map)
{
	int fd;

	fd = open(map, O_RDONLY);
	if (fd < 0)
	{
		ft_printf_error("Error\n%s: map not found", map);
		exit(1);
	}
	if (!check_map_extension(map))
	{
		ft_printf_error("Error\n%s: wrong file extension", map);
		exit(1);
	}
	if (check_identifier(fd) == 1)
		exit(1);


	printf("Valid !");
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	check_map(argv[1]);
}
