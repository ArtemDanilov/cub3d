/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:59 by username          #+#    #+#             */
/*   Updated: 2026/05/18 14:18:23 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIB_H
# define LIB_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 10
# endif

# include <unistd.h>
# include <stdio.h>
# include <fcntl.h>
# include <stdlib.h>
# include <stdint.h>
# include <errno.h>
# include <string.h>
# include "minilibx/mlx.h"
# include "libft/libft.h"

# define KEY_ESC 65307
# define KEY_LEFT 65361
# define KEY_RIGHT 65363
# define KEY_W 119
# define KEY_S 115
# define KEY_A 97
# define KEY_D 100

# define COLOR_RED "\033[0;31m"
# define COLOR_RESET "\033[0m"

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color;
	int		c_color;
	int		duplicates;
}	t_textures;

typedef struct s_position
{
	double	pos_x;
	double	pos_y;
	double	dir_x;
	double	dir_y;
	double	plane_x;
	double	plane_y;
}	t_position;

typedef struct s_data
{
	char		**map;
	void		*mlx;
	void		*mlx_win;
	int			rows;
	int			row_len;
	int			rect_size;
	t_textures	*textures;
	t_position	*position;
}	t_data;

typedef struct s_img
{
	void	*img;
	char	*addr;
	int		bits_per_pixel;
	int		length;
	int		endian;
}				t_img;

char	*get_next_line(int fd);

//	....Parsing
char	*skip_spaces(char *str);
int		is_rgb(char *str);
void	print_error(char *msg);
char	*get_file_extension(char *path);

void	free_map(t_data *data);
void	parse_textures(char *line, t_textures *textures);
void	free_textures(t_textures *textures);
void	parse_map(char *map_str, t_data *data);
int		parsing(int fd, t_data *data);

// ....Parsing validation
int	data_validation(t_data *data);
int	is_texture_path_valid(char *path);
int	is_map(char *line);

#endif
