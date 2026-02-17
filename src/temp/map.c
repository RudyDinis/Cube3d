#include "../../includes/cube3d.h"


char **generate_map(int width, int height)
{
    // alloue la map
    char **map = malloc(sizeof(char *) * height);
    if (!map)
        return NULL;

    for (int y = 0; y < height; y++)
    {
        map[y] = malloc(sizeof(char) * (width + 1));
        if (!map[y])
        {
            for (int i = 0; i < y; i++)
                free(map[i]);
            free(map);
            return NULL;
        }

        for (int x = 0; x < width; x++)
        {
            // bords = murs
            if (y == 0 || y == height - 1 || x == 0 || x == width - 1)
                map[y][x] = '1';
            else
                map[y][x] = '0'; // initialisation à vide
        }
        map[y][width] = '\0';
    }

    // créer un chemin sinueux
    int x = 1, y = 1;
    int end_x = width - 2;
    int end_y = height - 2;
    while (x != end_x || y != end_y)
    {
        map[y][x] = '0'; // chemin
        if (rand() % 2)
        {
            if (x < end_x) x++;
            else if (x > end_x) x--;
        }
        else
        {
            if (y < end_y) y++;
            else if (y > end_y) y--;
        }
    }
    map[end_y][end_x] = '0';

    // ajouter des îlots de murs aléatoires (20% de chance)
    for (int i = 1; i < height-1; i++)
        for (int j = 1; j < width-1; j++)
            if (map[i][j] == '0' && rand() % 5 == 0)
            {    
                if (rand() % 5 == 0)
                    map[i][j] = 'P';
                else
                    map[i][j] = '1';
            }
    // placer le joueur sur un point du chemin (par exemple départ)
    map[1][1] = 'J';

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