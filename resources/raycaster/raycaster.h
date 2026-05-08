/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlasov <anvlasov@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:26:00 by anvlasov          #+#    #+#             */
/*   Updated: 2026/05/08 22:23:00 by anvlasov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAYCASTER_H
# define RAYCASTER_H

# include "mlx.h"
# include "../../libft/libft.h"
# include <stdlib.h>
# include <math.h>
# include <fcntl.h>
# include <unistd.h>
# include <stdio.h>

# ifndef M_PI
#  define M_PI 3.14159265358979323846
# endif

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

/* Key codes (Linux X11) */
# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100
# define KEY_LEFT  65361
# define KEY_RIGHT 65363

/* Map settings */
# define MAP_SIZE 64
# define MINI_S   16
# define MINI_Y   10

/* Helper structs */
typedef struct s_rect
{
	int	x;
	int	y;
	int	w;
	int	h;
}				t_rect;

typedef struct s_line
{
	int	x0;
	int	y0;
	int	x1;
	int	y1;
}				t_line;

/* Raycasting helper structure */
typedef struct s_ray
{
	int		r;
	float	ra;
	float	vx;
	float	vy;
	float	hx;
	float	hy;
	float	dis_v;
	float	dis_h;
	float	rx;
	float	ry;
	int		is_vert;
}			t_ray;

typedef struct s_textures
{
	char	*no_texture;
	char	*so_texture;
	char	*we_texture;
	char	*ea_texture;
	int		f_color;
	int		c_color;
}				t_textures;

/* Main data structure */
typedef struct s_data
{
	void		*mlx;
	void		*win;
	void		*img;
	char		*addr;
	int			bpp;
	int			ll;
	int			endian;
	int			win_w;
	int			win_h;
	float		px;
	float		py;
	float		pdx;
	float		pdy;
	float		pa;
	char		**map;
	int			map_w;
	int			map_h;
	int			rows;
	int			row_len;
	t_textures	textures;
	t_ray		rays[120];
	int			w;
	int			a;
	int			s;
	int			d;
	int			left;
	int			right;
}				t_data;

/* Function prototypes */

/* Utils (raycaster_utils.c) */
float	deg_to_rad(int a);
int		fix_ang(int a);
int		rgb(float r, float g, float b);
void	put_pixel(t_data *d, int x, int y, int color);

/* 2D Functions (raycaster_2d.c) */
void	draw_line(t_data *d, t_line ln, int color);
void	fill_rect(t_data *d, t_rect rt, int color);
void	draw_map_2d(t_data *d);
void	draw_player_2d(t_data *d);
void	draw_rays_2d(t_data *d);

/* 3D/Logic Functions (raycaster_3d.c) */
void	calculate_rays(t_data *d);
void	draw_sky_and_floor(t_data *d);
void	draw_3d_scene(t_data *d);
void	check_vertical_lines(t_data *d, t_ray *ry);
void	check_horizontal_lines(t_data *d, t_ray *ry);

/* Parsing (resources/parsing/...) */
int		parsing(char *path, t_data *data);
void	parse_textures(char *line, t_textures *textures);
char	*skip_spaces(char *str);
void	parse_map(char *map_str, t_data *data);
char	*get_next_line(int fd);
void	free_map(t_data *data);
void	free_textures(t_textures *textures);
int		is_rgb(char *str);
int		textures_existance(t_textures *textures);

#endif
