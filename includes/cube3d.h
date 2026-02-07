/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cube3d.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rdinis <rdinis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 17:24:03 by rdinis            #+#    #+#             */
/*   Updated: 2026/02/07 19:38:31 by rdinis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBE3D_H
# define CUBE3D_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <time.h>
# include <mlx.h>
# include <math.h>

# include "../utils/libft/libft.h"

//TEMP INCLUDE
char **generate_map(int width, int height);
void print_map(char **map, int height);
void free_map(char **map, int height);



typedef struct s_img {
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		line_length;
	int		endian;
}	t_img;

typedef struct s_player
{
	int		x;
	int		y;
	int		r;
	t_img	data_img;
}	t_player;


typedef struct s_minimap
{
	void	*ground;
	void	*wall;
}	t_minimap;

typedef struct s_map
{
	char	**map;
	int		height;
	int		width;
}	t_map;


typedef struct s_data
{
	void		*mlx;
	void		*mlx_win;
	t_map		*map;
	t_minimap	*minimap;
	t_player	*player;
}	t_data;

void	init_player(t_data *data);

#endif
