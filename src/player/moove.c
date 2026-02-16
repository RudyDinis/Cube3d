#include "../../includes/cube3d.h"

int can_moove(t_data *data, double dx, double dy)
{
	(void) data;
	
	if (data->map->map[(int)(data->player->y + dy) / 32][(int)(data->player->x + dx) / 32] != '1')
		return (1);
	return (0);
}
