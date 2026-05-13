/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:03 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:22 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

void	init_texture_data(t_textures *textures)
{
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
	t_data		*data;
	char		*path;
	int			fd;
	// t_img		img;

	if (ac < 2 || !av[1] || !av[1][0])
	{
		print_error("Parameter is missing");
		return (1);
	}
	path = av[1];

	if (ft_strncmp(get_file_extension(path), "cub", 3) != 0)
	{
		print_error("The file extension is not valid");
		return (1);
	}
	fd = open(path, O_RDONLY);
	if (fd < 0)
	{
		print_error("File is empty");
		return (1);
	}

	data = malloc(sizeof(t_data));
	data->textures = malloc(sizeof(t_textures));
	
	init_texture_data(data->textures);
	parsing(fd, data);

	if (!data_validation(data))
	{
		free_map(data);
		free_textures(data->textures);
		free(data);
		return (1);
	}

	// ..........Show allocated array
	// for (int j = 0; j < 14; j++)
	// {
	// 	for (int k = 0; k < 33; k++)
	// 		printf("%c", data->map[j][k]);
	// 	printf("\n");
	// }

	// ..........Check textures existance
	// printf("%s\n", data->textures->ea_texture);
	// printf("%s\n", data->textures->so_texture);
	// printf("%d\n", data->textures->f_color);
	// printf("%d\n", data->textures->c_color);
	
	free_map(data);
	free_textures(data->textures);
	free(data);

	// data->mlx = mlx_init();
	// data->mlx_win = mlx_new_window(data->mlx, 1280, 768, "Cub3D");
	// img.img = mlx_new_image(data->mlx, 1280, 768);
    // img.addr = mlx_get_data_addr(img.img, &img.bits_per_pixel, &img.length, &img.endian);
    
	// // .....Start Tests
	// for (int i = 0; i < 64; i++)
	// 	for (int j = 0; j < 64; j++)
    // 		my_mlx_pixel_put(&img, i, j, data->textures->f_color);
    
    // mlx_put_image_to_window(data->mlx, data->mlx_win, img.img, 0, 0);
	// // .....End Tests
    // mlx_loop(data->mlx);
	
	return (0);
}
