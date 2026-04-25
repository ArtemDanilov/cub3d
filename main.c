/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:03 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/25 11:22:33 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	init_texture_data()
{
	t_textures	*textures;
	textures = malloc(sizeof(t_textures));

	textures = malloc(sizeof(t_textures));
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->f_color = 0;
	textures->c_color = 0;
}

void	my_mlx_pixel_put(t_img *img, int x, int y, int color)
{
	char	*dst;

	dst = img->addr + (y * img->length + x * (img->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

int	main(int ac, char **av)
{
	(void)ac;
	(void)**av;
	t_textures	*textures;
	t_data		*data;
	t_img		img;
	
	data = malloc(sizeof(t_data));

	textures = malloc(sizeof(t_textures));
	init_texture_data(textures);

	parsing("maps/1.cub", textures);

	data->mlx = mlx_init();
	data->mlx_win = mlx_new_window(data->mlx, 1280, 768, "Cub3D");
	img.img = mlx_new_image(data->mlx, 1280, 768);
    img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.length, &img.endian);
    
	// .....Start Tests
	for (int i = 0; i < 64; i++)
		for (int j = 0; j < 64; j++)
    		my_mlx_pixel_put(&img, i, j, textures->f_color);
    
    mlx_put_image_to_window(data->mlx, data->mlx_win, img.img, 0, 0);
	// .....End Tests
    mlx_loop(data->mlx);
	
	return (0);
}
