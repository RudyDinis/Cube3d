#include "../../includes/cube3d.h"

char **generate_map(int width, int height)
{
	char **map = malloc(sizeof(char *) * height);
	if (!map)
		return NULL;

	for (int y = 0; y < height; y++)
	{
		map[y] = malloc(sizeof(char) * (width + 1));
		if (!map[y])
			return NULL;

		for (int x = 0; x < width; x++)
		{
			map[y][x] = (rand() % 2) + '0'; // '0' ou '1'
		}
		map[y][width] = '\0'; // fin de ligne
	}
	return map;
}

void print_map(char **map, int height)
{
	for (int y = 0; y < height; y++)
		printf("%s\n", map[y]);
}

void free_map(char **map, int height)
{
	for (int y = 0; y < height; y++)
		free(map[y]);
	free(map);
}