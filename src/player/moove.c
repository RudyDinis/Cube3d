#include "../../includes/cube3d.h"

int can_moove(t_data *data, double dx, double dy)
{
    (void) data;
    
   	printf("%f %f %d %d %c\n", data->player->x + dx, data->player->y + dy,
        (int)(data->player->x + dx) / 32, (int)(data->player->y + dy) / 32,
        data->map->map[(int)(data->player->x + dx) / 32][(int)(data->player->y + dy) / 32]);

    if (data->map->map[(int)(data->player->y + dy) / 32][(int)(data->player->x + dx) / 32] != '1')
        return (1);
    return (0);
}