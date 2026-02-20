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

char *fill_map(int fd, char *map, t_id *id)
{
	char *copy;
	char *gnl;
	size_t size;
	size_t i;
	size_t j;

	j = 0,
	i = 0;
	size = get_map_size(fd);
	fd = open(map, O_RDONLY);
	check_identifier(fd, id);
	copy = ft_calloc(size + 1, 1);
	gnl = get_next_line(fd, 0);
	while (gnl && *gnl == '\n')
	{
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	while (gnl)
	{
		ft_memcpy(&copy[i], gnl, ft_strlen(gnl));
		i += ft_strlen(gnl);
		while (j < i && copy[j])
		{
			if (copy[j] == ' ')
				copy[j] = '5';
			j++;
		}
		free(gnl);
		gnl = get_next_line(fd, 0);
	}
	close(fd);
	return copy;
}


int check_closed(char *map)
{
	int i;
	int y;
	int size;
	int line;
	char **split;

	line = 0;
	i = 0;
	size = 0;
	split = ft_split(map, "\n");
	if (!split)
		return 0; //TODO gérer l'erreur ici
	while (split[i])
	{
		y = 0;
		ft_printf("%s\n", split[i]);
		while (split[i][y])
		{
			if (split[i][y] == '0')
			{
				if (i == 0 || !split[i + 1])
				{
					ft_printf_error("WRONG"); //TODO faire ça bien
					return 1;
				}
				else if (y == 0 || !split[i][y + 1])
				{
					ft_printf_error("WRONG"); //TODO faire ça bien
					return 1;
				}
				else if (split[i][y + 1] == '5' || split[i][y - 1] == '5' || split[i + 1][y] == '5' || split[i - 1][y] == '5')
				{
					ft_printf_error("WRONG"); //TODO faire ça bien
					return 1;
				}
			}
			y++;
		}
		i++;
	}
	free_everything((void **)split);
	return 0;
}

void check_map(char *map, t_id *id)
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
	if (check_identifier(fd, id) == 1)
		exit(1);
	printf("Valid !");
	//char *copy = fill_map(fd, map, id);
	//printf("%s\n", copy);
	//check_closed(copy);
}

t_id *malloc_id(void)
{
	t_id *id;
	int i;

	i = 0;
	id = ft_calloc(1, sizeof(t_id));
	id->id = ft_calloc(6 + 1, sizeof(char *));
	id->id[0] = ft_strdup("NO");
	id->id[1] = ft_strdup("SO");
	id->id[2] = ft_strdup("EA");
	id->id[3] = ft_strdup("WE");
	id->id[4] = ft_strdup("F");
	id->id[5] = ft_strdup("C");
	id->done = ft_calloc(6 + 1, sizeof(char *));
	return id;
}

int main(int argc, char **argv)
{
	if (argc != 2)
		return 1;
	t_id *id;

	id = malloc_id();
	check_map(argv[1], id);
}
