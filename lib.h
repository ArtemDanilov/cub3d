/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lib.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:59 by username          #+#    #+#             */
/*   Updated: 2026/04/25 11:21:26 by artemdanilo      ###   ########.fr       */
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

typedef struct s_textures
{
	char	**map;
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color;
	int		c_color;
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
	void		*mlx;
	void		*mlx_win;
	int			rect_size;
	t_textures	textures;
	t_position	position;
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
void	parse_textures(char *line, t_textures *textures);
int		parsing(char *path, t_textures *textures);

#endif
