/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bbouarab <bbouarab@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/25 11:30:25 by bbouarab          #+#    #+#             */
/*   Updated: 2026/02/25 13:55:15 by bbouarab         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

# include "../libft/libft.h"

# define XPM_PARAM "XPM file: wrong number of parameters"
# define XPM_TEXTURE "XPM file: texture size not supported"
# define XPM_COLOR "XPM file: incorrect number of color"
# define XPM_PIXEL "XPM file: number of character per pixel not supported"
# define XPM_NUM "XPM file: numeric arguments required"

typedef struct s_id {
	char				**id;
	char				**done;
	struct s_map_data	*data;
}	t_id;

typedef struct s_map_data {
	char	*no_texture;
	char	*so_texture;
	char	*ea_texture;
	char	*we_texture;
	char	**c_color;
	char	**f_color;
}	t_map_data;

int		check_valid_char(char c);
int		check_xpm(char *texture);
int		check_map_extension(char *path);
int		check_id_order(char **split, t_id *id, int pos);
t_id	*malloc_id(t_map_data *data);
void	check_identifier(int fd, t_id *id);
void	skip_newline(char **line, int fd);
void	replace_space(char *copy, size_t *j, size_t i);
void	free_id(t_id *id);
void	check_map(char *map, t_map_data *data);
char	*fill_map(int fd, char *map, t_id *id);
size_t	get_map_size(int fd, t_id *id);

#endif
