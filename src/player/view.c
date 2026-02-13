#include "../../includes/cube3d.h"

int get_pixel_color(t_data *data, int x, int y)
{
    char *pixel;
    if (y < 0)
        y = 0;
    if (y > 31)
        y = 31;
    pixel = data->minimap->wall_addr + (y * data->minimap->wall_size_line + x * (data->minimap->wall_bpp / 8));
    return *(unsigned int *)pixel;
}

void draw_wall(t_data *data, int col, double wallHeight)
{
    int y;
    int y_start;
    int y_end;
    int tex_y;
    int tex_x;
    int color;

    y_start = (1080 / 2) - (int)(wallHeight / 2);
    y_end = (1080 / 2) + (int)(wallHeight / 2);
    if (y_start < 0)
        y_start = 0;
    if (y_end > 1080)
        y_end = 1080;
    y = y_start;
    while (y < y_end)
    {
        tex_y = (int)((y - y_start) * 32 / wallHeight);
        tex_x = col % 32;
        color = get_pixel_color(data, tex_x, tex_y);
        my_mlx_pixel_put(&data->vision, col, y, color);
        y++;
    }
}
int raycasting2(t_data *data, t_ray *vars)
{
    if (data->map->map[vars->mapY][vars->mapX] == '1')
    {
        vars->distCorr = vars->distance * cos(vars->angle - (data->player->r * 3.14159265 / 180.0));
        if (vars->distCorr <= 0.1)
            vars->distCorr = 0.1;
        vars->wallHeight = 10000.0 / vars->distCorr;
        draw_wall(data, vars->col, vars->wallHeight);
        return (1);
    }
    return (0);
}

void raycasting(t_data *data)
{
    t_ray vars;

    if (data->map->width > data->map->height)
        vars.max = data->map->width;
    else
        vars.max = data->map->height;
    vars.col = 0;
    while (vars.col < 1920)
    {
        vars.angle = (data->player->r - data->player->fov / 2.0 + ((double)vars.col / 1920.0) * data->player->fov) * 3.14159265 / 180.0;
        vars.distance = 0.0;
        while (vars.distance < vars.max * 32)
        {
            vars.x = data->player->x + cos(vars.angle) * vars.distance;
            vars.y = data->player->y + sin(vars.angle) * vars.distance;
            vars.mapX = (int)floor(vars.x / 32);
            vars.mapY = (int)floor(vars.y / 32);
            if (vars.mapX < 0 || vars.mapY < 0 || vars.mapX >= data->map->width || vars.mapY >= data->map->height)
                break;
            if (raycasting2(data, &vars) == 1)
                break;
            vars.distance += 1.0;
        }
        vars.col++;
    }
}

void render_frame(t_data *data)
{
    int x;
    int y;

    y = 0;
    while (y < 1080)
    {
        x = 0;
        while (x < 1920)
        {
            if (y < 1080/2)
                my_mlx_pixel_put(&data->vision, x, y, 0x77b5fe);
            else
                my_mlx_pixel_put(&data->vision, x, y, 0x000000);
            x++;
        }
        y++;
    }
    raycasting(data);
    mlx_put_image_to_window(data->mlx, data->mlx_win, data->vision.img, 0, 0);
    draw_player_arrow(data, 0);
    load_minimap(data);
}
