/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:22:03 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/21 13:21:20 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lib.h"

int	main(int ac, char **av)
{
	(void)ac;
	(void)**av;
	t_textures	*textures;
	
	textures = malloc(sizeof(t_textures));
	textures->no_texture = NULL;
	textures->so_texture = NULL;
	textures->we_texture = NULL;
	textures->ea_texture = NULL;
	textures->f_color = 0;
	textures->c_color = 0;
	
	parsing("maps/1.cub", textures);
	
	return (0);
}

	// char	**map;
	// char	*no_texture;
	// char	*so_texture;
	// char	*we_texture;
	// char	*ea_texture;
	// int		f_color;
	// int		c_color;