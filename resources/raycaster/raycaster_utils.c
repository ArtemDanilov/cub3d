/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycaster_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: anvlasov <anvlasov@student.42warsaw.pl>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/08 20:16:00 by anvlasov          #+#    #+#             */
/*   Updated: 2026/05/08 20:44:00 by anvlasov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

/*
** Convert degrees to radians
*/
float	deg_to_rad(int a)
{
	return (a * M_PI / 180.0);
}

/*
** Keep angle within [0..359] range
*/
int	fix_ang(int a)
{
	if (a > 359)
		a -= 360;
	if (a < 0)
		a += 360;
	return (a);
}

/*
** Put one pixel into the off-screen image buffer
*/
void	put_pixel(t_data *d, int x, int y, int color)
{
	char	*dst;

	if (x < 0 || x >= d->win_w || y < 0 || y >= d->win_h)
		return ;
	dst = d->addr + y * d->ll + x * (d->bpp / 8);
	*(unsigned int *)dst = color;
}

/*
** Pack float RGB [0..1] into 0xRRGGBB hex color
*/
int	rgb(float r, float g, float b)
{
	return (((int)(r * 255) & 0xFF) << 16)
		| (((int)(g * 255) & 0xFF) << 8)
		| ((int)(b * 255) & 0xFF);
}
