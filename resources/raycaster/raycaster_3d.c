/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_3d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlasov <anvlasov@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:16:00 by anvlasov          #+#    #+#             */
/*   Updated: 2026/05/08 22:25:00 by anvlasov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

typedef struct s_cast
{
	int		dof;
	int		mx;
	int		my;
	float	rx;
	float	ry;
	float	xo;
	float	yo;
	float	tan_v;
}			t_cast;

void	draw_sky_and_floor(t_data *d)
{
	fill_rect(d, (t_rect){0, 0, d->win_w, d->win_h / 2}, d->textures.c_color);
	fill_rect(d, (t_rect){0, d->win_h / 2, d->win_w, d->win_h / 2}, \
				d->textures.f_color);
}

void	check_vertical_lines(t_data *d, t_ray *ry)
{
	t_cast	c;

	c.dof = 0;
	ry->dis_v = 1000000;
	c.tan_v = tan(deg_to_rad(ry->ra));
	if (cos(deg_to_rad(ry->ra)) > 0.001)
	{
		c.rx = (((int)d->px >> 6) << 6) + 64;
		c.ry = (d->px - c.rx) * c.tan_v + d->py;
		c.xo = 64;
		c.yo = -c.xo * c.tan_v;
	}
	else if (cos(deg_to_rad(ry->ra)) < -0.001)
	{
		c.rx = (((int)d->px >> 6) << 6) - 0.0001;
		c.ry = (d->px - c.rx) * c.tan_v + d->py;
		c.xo = -64;
		c.yo = -c.xo * c.tan_v;
	}
	else
	{
		c.rx = d->px;
		c.ry = d->py;
		c.dof = 80;
	}
	while (c.dof < 80)
	{
		c.mx = (int)c.rx >> 6;
		c.my = (int)c.ry >> 6;
		if (c.mx >= 0 && c.mx < d->map_w && c.my >= 0 && c.my < d->map_h \
			&& d->map[c.my][c.mx] == '1')
		{
			c.dof = 80;
			ry->dis_v = cos(deg_to_rad(ry->ra)) * (c.rx - d->px) - \
						sin(deg_to_rad(ry->ra)) * (c.ry - d->py);
		}
		else
		{
			c.rx += c.xo;
			c.ry += c.yo;
			c.dof += 1;
		}
	}
	ry->vx = c.rx;
	ry->vy = c.ry;
}

void	check_horizontal_lines(t_data *d, t_ray *ry)
{
	t_cast	c;

	c.dof = 0;
	ry->dis_h = 1000000;
	c.tan_v = 1.0 / tan(deg_to_rad(ry->ra));
	if (sin(deg_to_rad(ry->ra)) > 0.001)
	{
		c.ry = (((int)d->py >> 6) << 6) - 0.0001;
		c.rx = (d->py - c.ry) * c.tan_v + d->px;
		c.yo = -64;
		c.xo = -c.yo * c.tan_v;
	}
	else if (sin(deg_to_rad(ry->ra)) < -0.001)
	{
		c.ry = (((int)d->py >> 6) << 6) + 64;
		c.rx = (d->py - c.ry) * c.tan_v + d->px;
		c.yo = 64;
		c.xo = -c.yo * c.tan_v;
	}
	else
	{
		c.rx = d->px;
		c.ry = d->py;
		c.dof = 80;
	}
	while (c.dof < 80)
	{
		c.mx = (int)c.rx >> 6;
		c.my = (int)c.ry >> 6;
		if (c.mx >= 0 && c.mx < d->map_w && c.my >= 0 && c.my < d->map_h \
			&& d->map[c.my][c.mx] == '1')
		{
			c.dof = 80;
			ry->dis_h = cos(deg_to_rad(ry->ra)) * (c.rx - d->px) - \
						sin(deg_to_rad(ry->ra)) * (c.ry - d->py);
		}
		else
		{
			c.rx += c.xo;
			c.ry += c.yo;
			c.dof += 1;
		}
	}
	ry->hx = c.rx;
	ry->hy = c.ry;
}

void	calculate_rays(t_data *d)
{
	int		r;
	t_ray	*ry;

	r = 0;
	while (r < 120)
	{
		ry = &d->rays[r];
		ry->r = r;
		ry->ra = fix_ang((int)(d->pa + 40 - r * 80.0 / 120.0));
		check_vertical_lines(d, ry);
		check_horizontal_lines(d, ry);
		ry->is_vert = 0;
		if (ry->dis_v < ry->dis_h)
		{
			ry->rx = ry->vx;
			ry->ry = ry->vy;
			ry->dis_h = ry->dis_v;
			ry->is_vert = 1;
		}
		else
		{
			ry->rx = ry->hx;
			ry->ry = ry->hy;
		}
		r++;
	}
}

static void	draw_strip(t_data *d, t_rect rt, int col)
{
	int	i;
	int	line_off;
	int	xw;

	line_off = (d->win_h / 2) - (rt.h >> 1);
	i = line_off;
	while (i < line_off + rt.h)
	{
		xw = 0;
		while (xw < rt.w)
		{
			put_pixel(d, rt.x + xw, i, col);
			xw++;
		}
		i++;
	}
}

void	draw_3d_scene(t_data *d)
{
	int		r;
	int		ca;
	int		lh;
	int		col;
	t_ray	*ry;
	int		x1;

	draw_sky_and_floor(d);
	r = 0;
	while (r < 120)
	{
		ry = &d->rays[r];
		ca = fix_ang((int)(d->pa - ry->ra));
		lh = (MAP_SIZE * d->win_h) / (int)(ry->dis_h * cos(deg_to_rad(ca)));
		if (lh > d->win_h)
			lh = d->win_h;
		col = rgb(0, 0.8, 0);
		if (ry->is_vert)
			col = rgb(0, 0.6, 0);
		x1 = (r * d->win_w) / 120;
		draw_strip(d, (t_rect){x1, 0, ((r + 1) * d->win_w) / 120 - x1, lh}, col);
		r++;
	}
}

static void	update_player(t_data *d)
{
	if (d->a)
		d->pa = fix_ang((int)(d->pa + 1.5));
	if (d->d)
		d->pa = fix_ang((int)(d->pa - 1.5));
	d->pdx = cos(deg_to_rad((int)d->pa));
	d->pdy = -sin(deg_to_rad((int)d->pa));
	if (d->w)
	{
		d->px += d->pdx * 1.5;
		d->py += d->pdy * 1.5;
	}
	if (d->s)
	{
		d->px -= d->pdx * 1.5;
		d->py -= d->pdy * 1.5;
	}
	if (d->left)
	{
		d->px += d->pdy * 1.5;
		d->py -= d->pdx * 1.5;
	}
	if (d->right)
	{
		d->px -= d->pdy * 1.5;
		d->py += d->pdx * 1.5;
	}
}

static int	render_frame(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	update_player(d);
	fill_rect(d, (t_rect){0, 0, d->win_w, d->win_h}, rgb(0.3, 0.3, 0.3));
	calculate_rays(d);
	draw_3d_scene(d);
	draw_map_2d(d);
	draw_rays_2d(d);
	draw_player_2d(d);
	mlx_put_image_to_window(d->mlx, d->win, d->img, 0, 0);
	return (0);
}

static int	handle_keydown(int key, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (key == KEY_ESC)
	{
		mlx_destroy_image(d->mlx, d->img);
		mlx_destroy_window(d->mlx, d->win);
		exit(0);
	}
	if (key == KEY_W)
		d->w = 1;
	if (key == KEY_A)
		d->a = 1;
	if (key == KEY_S)
		d->s = 1;
	if (key == KEY_D)
		d->d = 1;
	if (key == KEY_LEFT)
		d->left = 1;
	if (key == KEY_RIGHT)
		d->right = 1;
	return (0);
}

static int	handle_keyup(int key, void *param)
{
	t_data	*d;

	d = (t_data *)param;
	if (key == KEY_W)
		d->w = 0;
	if (key == KEY_A)
		d->a = 0;
	if (key == KEY_S)
		d->s = 0;
	if (key == KEY_D)
		d->d = 0;
	if (key == KEY_LEFT)
		d->left = 0;
	if (key == KEY_RIGHT)
		d->right = 0;
	return (0);
}

static int	handle_close(void *param)
{
	t_data	*d;

	d = (t_data *)param;
	mlx_destroy_image(d->mlx, d->img);
	mlx_destroy_window(d->mlx, d->win);
	exit(0);
	return (0);
}

static void	init_player(t_data *d)
{
	int	y;
	int	x;

	y = -1;
	while (++y < d->map_h)
	{
		x = -1;
		while (++x < d->map_w)
		{
			if (ft_strchr("NSEW", d->map[y][x]))
			{
				d->px = x * 64 + 32;
				d->py = y * 64 + 32;
				if (d->map[y][x] == 'N')
					d->pa = 90;
				else if (d->map[y][x] == 'S')
					d->pa = 270;
				else if (d->map[y][x] == 'E')
					d->pa = 0;
				else if (d->map[y][x] == 'W')
					d->pa = 180;
				return ;
			}
		}
	}
}

int	main(int argc, char **argv)
{
	t_data		d;
	char		*path;

	if (argc == 2)
		path = argv[1];
	else if (argc == 1)
		path = "maps/1.cub";
	else
		return (1);
	ft_memset(&d, 0, sizeof(t_data));
	parsing(path, &d);
	d.map_h = d.rows;
	d.map_w = d.row_len;
	init_player(&d);
	d.pdx = cos(deg_to_rad((int)d.pa));
	d.pdy = -sin(deg_to_rad((int)d.pa));
	d.mlx = mlx_init();
	mlx_get_screen_size(d.mlx, &d.win_w, &d.win_h);
	d.win = mlx_new_window(d.mlx, d.win_w, d.win_h, "Cube 3D");
	d.img = mlx_new_image(d.mlx, d.win_w, d.win_h);
	d.addr = mlx_get_data_addr(d.img, &d.bpp, &d.ll, &d.endian);
	mlx_hook(d.win, 2, 1L << 0, handle_keydown, &d);
	mlx_hook(d.win, 3, 1L << 1, handle_keyup, &d);
	mlx_hook(d.win, 17, 0, handle_close, &d);
	mlx_loop_hook(d.mlx, render_frame, &d);
	mlx_loop(d.mlx);
	return (0);
}
