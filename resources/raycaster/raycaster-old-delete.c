
#include "mlx.h"
#include <stdlib.h>
#include <math.h>

#ifndef M_PI
# define M_PI 3.14159265358979323846
#endif

// Window dimensions
# define WIN_W 1024
# define WIN_H 510

// Key codes (Linux X11)
# define KEY_ESC   65307
# define KEY_W     119
# define KEY_A     97
# define KEY_S     115
# define KEY_D     100

//-----------------------------MAP----------------------------------------------
# define MAP_X    8
# define MAP_Y    8
# define MAP_SIZE 64

static int	g_map[] =
{
	1, 1, 1, 1, 1, 1, 1, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 1, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 0, 0, 0, 0, 1, 0, 1,
	1, 0, 0, 0, 0, 0, 0, 1,
	1, 1, 1, 1, 1, 1, 1, 1,
};

//-----------------------------TYPES--------------------------------------------
// Mirrors solong's t_data struct (solong-final2/solong.h)
typedef struct s_data
{
	void	*mlx;
	void	*win;
	void	*img;
	char	*addr;       // raw pixel buffer (from mlx_get_data_addr)
	int		bpp;         // bits per pixel
	int		ll;          // line length in bytes
	int		endian;
	// player state
	float	px;
	float	py;
	float	pdx;
	float	pdy;
	float	pa;
}			t_data;

//-----------------------------UTILS--------------------------------------------
static float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}

static int	fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

// Put one pixel into the off-screen image buffer (solong pattern)
static void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= WIN_W || y < 0 || y >= WIN_H)
		return ;
	dst = d->addr + y * d->ll + x * (d->bpp / 8);
	*(unsigned int *)dst = color;
}

// Pack float RGB [0..1] into 0xRRGGBB
static int	rgb(float r, float g, float b)
{
	return (((int)(r * 255) & 0xFF) << 16)
		| (((int)(g * 255) & 0xFF) << 8)
		| ((int)(b * 255) & 0xFF);
}

// Fill a rectangle with the current color
static void	fill_rect(t_data *d, int x, int y, int w, int h, int color)
{
	int	ix;
	int	iy;

	iy = y;
	while (iy < y + h)
	{
		ix = x;
		while (ix < x + w)
		{
			put_pixel(d, ix, iy, color);
			ix++;
		}
		iy++;
	}
}

// Bresenham line (solong uses mlx_put_image_to_window; here we draw per-pixel)
static void	draw_line(t_data *d, int x0, int y0, int x1, int y1, int color)
{
	int	dx;
	int	dy;
	int	sx;
	int	sy;
	int	err;
	int	e2;

	dx = abs(x1 - x0);
	dy = -abs(y1 - y0);
	sx = (x0 < x1) ? 1 : -1;
	sy = (y0 < y1) ? 1 : -1;
	err = dx + dy;
	while (1)
	{
		put_pixel(d, x0, y0, color);
		if (x0 == x1 && y0 == y1)
			break ;
		e2 = 2 * err;
		if (e2 >= dy)
		{
			err += dy;
			x0 += sx;
		}
		if (e2 <= dx)
		{
			err += dx;
			y0 += sy;
		}
	}
}

//-----------------------------DRAW MAP-----------------------------------------
// draws the map (2D top-down view, left side of window)
static void	draw_map_2d(t_data *d)
{
	int	x;
	int	y;
	int	xo;
	int	yo;
	int	color;

	y = 0;
	while (y < MAP_Y)
	{
		x = 0;
		while (x < MAP_X)
		{
			if (g_map[y * MAP_X + x] == 1)
				color = rgb(1, 1, 1);
			else
				color = rgb(0, 0, 0);
			xo = x * MAP_SIZE;
			yo = y * MAP_SIZE;
			fill_rect(d, xo + 1, yo + 1, MAP_SIZE - 2, MAP_SIZE - 2, color);
			x++;
		}
		y++;
	}
}

//-----------------------------DRAW PLAYER--------------------------------------
// draws the player dot and direction line on the 2D map
static void	draw_player_2d(t_data *d)
{
	int	col;
	int	lx;
	int	ly;

	col = rgb(1, 1, 0);
	// 4x4 dot for the player
	fill_rect(d, (int)d->px - 2, (int)d->py - 2, 5, 5, col);
	// direction line
	lx = (int)(d->px + d->pdx * 20);
	ly = (int)(d->py + d->pdy * 20);
	draw_line(d, (int)d->px, (int)d->py, lx, ly, col);
}

//-----------------------------SKY & FLOOR--------------------------------------
// draws solid sky (cyan) and floor (dark blue) on the right 3D viewport
static void	draw_sky_and_floor(t_data *d)
{
	fill_rect(d, 526, 0, 480, 160, rgb(0, 1, 1));
	fill_rect(d, 526, 160, 480, 160, rgb(0, 0, 0.6));
}

//-----------------------------RAYCASTING---------------------------------------
/*
** Casts a ray to check for intersections with vertical grid lines.
*/
static void	check_vertical_lines(t_data *d, float ra,
				float *vx, float *vy, float *dis_v)
{
	int		dof;
	int		mx;
	int		my;
	int		mp;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	tan_v;

	dof = 0;
	xo = 0;
	yo = 0;
	*dis_v = 100000;
	tan_v = tan(deg_to_rad(ra));
	if (cos(deg_to_rad(ra)) > 0.001)
	{
		rx = (((int)d->px >> 6) << 6) + 64;
		ry = (d->px - rx) * tan_v + d->py;
		xo = 64;
		yo = -xo * tan_v;
	}
	else if (cos(deg_to_rad(ra)) < -0.001)
	{
		rx = (((int)d->px >> 6) << 6) - 0.0001;
		ry = (d->px - rx) * tan_v + d->py;
		xo = -64;
		yo = -xo * tan_v;
	}
	else
	{
		rx = d->px;
		ry = d->py;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		mp = my * MAP_X + mx;
		if (mp > 0 && mp < MAP_X * MAP_Y && g_map[mp] == 1)
		{
			dof = 8;
			*dis_v = cos(deg_to_rad(ra)) * (rx - d->px)
				- sin(deg_to_rad(ra)) * (ry - d->py);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	*vx = rx;
	*vy = ry;
}

/*
** Casts a ray to check for intersections with horizontal grid lines.
*/
static void	check_horizontal_lines(t_data *d, float ra,
				float *hx, float *hy, float *dis_h)
{
	int		dof;
	int		mx;
	int		my;
	int		mp;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	tan_v;

	dof = 0;
	xo = 0;
	yo = 0;
	*dis_h = 100000;
	tan_v = 1.0 / tan(deg_to_rad(ra));
	if (sin(deg_to_rad(ra)) > 0.001)
	{
		ry = (((int)d->py >> 6) << 6) - 0.0001;
		rx = (d->py - ry) * tan_v + d->px;
		yo = -64;
		xo = -yo * tan_v;
	}
	else if (sin(deg_to_rad(ra)) < -0.001)
	{
		ry = (((int)d->py >> 6) << 6) + 64;
		rx = (d->py - ry) * tan_v + d->px;
		yo = 64;
		xo = -yo * tan_v;
	}
	else
	{
		rx = d->px;
		ry = d->py;
		dof = 8;
	}
	while (dof < 8)
	{
		mx = (int)rx >> 6;
		my = (int)ry >> 6;
		mp = my * MAP_X + mx;
		if (mp > 0 && mp < MAP_X * MAP_Y && g_map[mp] == 1)
		{
			dof = 8;
			*dis_h = cos(deg_to_rad(ra)) * (rx - d->px)
				- sin(deg_to_rad(ra)) * (ry - d->py);
		}
		else
		{
			rx += xo;
			ry += yo;
			dof += 1;
		}
	}
	*hx = rx;
	*hy = ry;
}

/*
** Computes wall slice height, applies fish-eye correction, draws vertical line.
*/
static void	draw_3d_walls(t_data *d, int r, float ra, float dis_h, int is_vert)
{
	int	ca;
	int	line_h;
	int	line_off;
	int	col;
	int	i;
	int	x;

	ca = fix_ang((int)(d->pa - ra));
	dis_h = dis_h * cos(deg_to_rad(ca));
	line_h = (MAP_SIZE * 320) / (int)dis_h;
	if (line_h > 320)
		line_h = 320;
	line_off = 160 - (line_h >> 1);
	// darker shade for vertical wall hits (solong-style brightness differentiation)
	if (is_vert)
		col = rgb(0, 0.6, 0);
	else
		col = rgb(0, 0.8, 0);
	x = r * 8 + 530;
	i = line_off;
	while (i < line_off + line_h)
	{
		put_pixel(d, x, i, col);
		put_pixel(d, x + 1, i, col);
		put_pixel(d, x + 2, i, col);
		put_pixel(d, x + 3, i, col);
		put_pixel(d, x + 4, i, col);
		put_pixel(d, x + 5, i, col);
		put_pixel(d, x + 6, i, col);
		put_pixel(d, x + 7, i, col);
		i++;
	}
}

/*
** Main ray loop: casts 60 rays over a 60-degree FOV.
*/
static void	draw_rays_2d(t_data *d)
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

	draw_sky_and_floor(d);
	ra = fix_ang((int)(d->pa + 30));
	r = 0;
	while (r < 60)
	{
		check_vertical_lines(d, ra, &vx, &vy, &dis_v);
		check_horizontal_lines(d, ra, &hx, &hy, &dis_h);
		is_vert = 0;
		if (dis_v < dis_h)
		{
			rx = vx;
			ry = vy;
			dis_h = dis_v;
			is_vert = 1;
		}
		else
		{
			rx = hx;
			ry = hy;
		}
		// draw 2D ray on the map
		draw_line(d, (int)d->px, (int)d->py, (int)rx, (int)ry, rgb(0, 0.8, 0));
		draw_3d_walls(d, r, ra, dis_h, is_vert);
		ra = fix_ang((int)(ra - 1));
		r++;
	}
}

//-----------------------------FRAME--------------------------------------------
// Called every loop iteration (mlx_loop_hook pattern from solong/start.c)
static int	render_frame(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	// clear the image buffer (dark grey background)
	fill_rect(d, 0, 0, WIN_W, WIN_H, rgb(0.3, 0.3, 0.3));
	draw_map_2d(d);
	draw_rays_2d(d);
	draw_player_2d(d);
	// push image to window (solong pattern: mlx_put_image_to_window)
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}

//-----------------------------INPUT--------------------------------------------
// Key handler (mirrors solong's handle_keypress in movement.c)
static int	handle_keypress(int key, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	if (key == KEY_A)
	{
		d->pa = fix_ang((int)(d->pa + 5));
		d->pdx = cos(deg_to_rad((int)d->pa));
		d->pdy = -sin(deg_to_rad((int)d->pa));
	}
	if (key == KEY_D)
	{
		d->pa = fix_ang((int)(d->pa - 5));
		d->pdx = cos(deg_to_rad((int)d->pa));
		d->pdy = -sin(deg_to_rad((int)d->pa));
	}
	if (key == KEY_W)
	{
		d->px += d->pdx * 5;
		d->py += d->pdy * 5;
	}
	if (key == KEY_S)
	{
		d->px -= d->pdx * 5;
		d->py -= d->pdy * 5;
	}
	return (0);
}

// Window close button (solong pattern: mlx_hook event 17)
static int	handle_close(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
	return (0);
}

//-----------------------------MAIN---------------------------------------------
int	main(void)
{
	t_data	d;

	// --- Init player (was in OpenGL init()) ---
	d.px = 150;
	d.py = 400;
	d.pa = 90;
	d.pdx = cos(deg_to_rad((int)d.pa));
	d.pdy = -sin(deg_to_rad((int)d.pa));

	// --- MiniLibX setup (mirrors solong/start.c main()) ---
	d.mlx = mlx_init();
	d.win = mlx_new_window(d.mlx, WIN_W, WIN_H, "Cube 3D");
	// Create off-screen image buffer (solong pattern)
	d.img = mlx_new_image(d.mlx, WIN_W, WIN_H);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.ll, &d.endian);

	// --- Hooks (mirrors solong/start.c) ---
	mlx_key_hook(d.win, handle_keypress, &d);
	mlx_hook(d.win, 17, 0, handle_close, &d);
	mlx_loop_hook(d.mlx, render_frame, &d);

	mlx_loop(d.mlx);
	return (0);
}
