#include "../../includes/cube3d.h"

int get_pixel_color(t_data *data, int x, int y)
{
    char *pixel;
    if (y < 0)
        y = 0;
    if (y > 31)
        y = 31;
    pixel = data->minimap->wall_addr + (y * data->minimap->wall_size_line + x * ( data->minimap->wall_bpp / 8));
    return *(unsigned int*)pixel;
}

void draw_wall(t_data *data, int col, double wallHeight)
{
    int y;
    int y_start = (1080 / 2) - (int)(wallHeight / 2);
    int y_end   = (1080 / 2) + (int)(wallHeight / 2);

    for (y = y_start; y < y_end; y++)
    {
        int tex_y = (int)((y - y_start) * 32 / wallHeight);
        int tex_x = col % 32;
        int color = get_pixel_color(data, tex_x, tex_y);
        my_mlx_pixel_put(&data->vision, col, y, color);
    }
}

void    raycasting(t_data *data)
{
    int col;
    double angle;
    double distance;
    int max;
    double x, y;
    int mapX, mapY;
    double distCorr;
    double wallHeight;

    if (data->map->width > data->map->height)
        max = data->map->width;
    else
        max = data->map->height;

    col = 0;
    while (col < 1920)
    {
       angle = (-data->player->r - data->player->fov / 2.0 + ((double)col / 1920.0) * data->player->fov) * 3.14159265 / 180.0;

        distance = 0.0;
        while (distance < max * 32)
        {
            x = data->player->x + cos(angle) * distance;
            y = data->player->y + sin(angle) * distance;
            mapX = (int)floor(x / 32);
            mapY = (int)floor(y / 32);
            if (mapX < 0 || mapY < 0 || mapX >= data->map->width || mapY >= data->map->height)
                break;
            if (data->map->map[mapY][mapX] == '1')
            {
                distCorr = distance * cos(angle - (data->player->r * 3.14159265 / 180.0));
                wallHeight = 10000.0 / distCorr;
                draw_wall(data, col, wallHeight);
                break;
            }
            distance += 1.0;
        }
        col++;
    }
}

void    render_frame(t_data *data)
{
    int x, y;
    for (y = 0; y < 1080; y++)
        for (x = 0; x < 1920; x++)
            my_mlx_pixel_put(&data->vision, x, y, 0x000000);
    raycasting(data);
	mlx_put_image_to_window(data->mlx, data->mlx_win, data->vision.img, 0, 0);
    draw_player_arrow(data, 0); 
	load_minimap(data);
}


void    rotate_player(t_data *data, double r)
{
    data->player->r += r;
    render_frame(data);
}