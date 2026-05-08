/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_2d.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlasov <anvlasov@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:16:00 by anvlasov          #+#    #+#             */
/*   Updated: 2026/05/08 22:24:00 by anvlasov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

#define MINI_X_CALC(d) (d->win_w - (d->map_w * MINI_S) - 10)

void	fill_rect(t_data *d, t_rect rt, int color)
{
	int	ix;
	int	iy;

	iy = rt.y;
	while (iy < rt.y + rt.h)
	{
		ix = rt.x;
		while (ix < rt.x + rt.w)
		{
			put_pixel(d, ix, iy, color);
			ix++;
		}
		iy++;
	}
}

static void	get_step(int p0, int p1, int *s)
{
	if (p0 < p1)
		*s = 1;
	else
		*s = -1;
}

void	draw_line(t_data *d, t_line ln, int color)
{
	int	v[6];

	v[0] = abs(ln.x1 - ln.x0);
	v[1] = -abs(ln.y1 - ln.y0);
	get_step(ln.x0, ln.x1, &v[2]);
	get_step(ln.y0, ln.y1, &v[3]);
	v[4] = v[0] + v[1];
	while (1)
	{
		put_pixel(d, ln.x0, ln.y0, color);
		if (ln.x0 == ln.x1 && ln.y0 == ln.y1)
			break ;
		v[5] = 2 * v[4];
		if (v[5] >= v[1])
		{
			v[4] += v[1];
			ln.x0 += v[2];
		}
		if (v[5] <= v[0])
		{
			v[4] += v[0];
			ln.y0 += v[3];
		}
	}
}

void	draw_map_2d(t_data *d)
{
	int		x;
	int		y;
	t_rect	rt;

	y = 0;
	while (y < d->map_h)
	{
		x = 0;
		while (x < d->map_w)
		{
			rt.x = MINI_X_CALC(d) + x * MINI_S;
			rt.y = MINI_Y + y * MINI_S;
			rt.w = MINI_S - 1;
			rt.h = MINI_S - 1;
			if (d->map[y][x] == '1')
				fill_rect(d, rt, rgb(1, 1, 1));
			else
				fill_rect(d, rt, rgb(0, 0, 0));
			x++;
		}
		y++;
	}
}

void	draw_player_2d(t_data *d)
{
	int		col;
	t_line	ln;
	float	scale;

	scale = (float)MINI_S / MAP_SIZE;
	col = rgb(1, 1, 0);
	fill_rect(d, (t_rect){MINI_X_CALC(d) + (int)(d->px * scale) - 2, \
				MINI_Y + (int)(d->py * scale) - 2, 4, 4}, col);
	ln.x0 = MINI_X_CALC(d) + (int)(d->px * scale);
	ln.y0 = MINI_Y + (int)(d->py * scale);
	ln.x1 = ln.x0 + (int)(d->pdx * 10);
	ln.y1 = ln.y0 + (int)(d->pdy * 10);
	draw_line(d, ln, col);
}

void	draw_rays_2d(t_data *d)
{
	int		r;
	float	scale;
	t_ray	*ry;

	scale = (float)MINI_S / MAP_SIZE;
	r = 0;
	while (r < 120)
	{
		ry = &d->rays[r];
		draw_line(d, (t_line){MINI_X_CALC(d) + (int)(d->px * scale), \
					MINI_Y + (int)(d->py * scale), \
					MINI_X_CALC(d) + (int)(ry->rx * scale), \
					MINI_Y + (int)(ry->ry * scale)}, rgb(0, 0.8, 0));
		r++;
	}
}
