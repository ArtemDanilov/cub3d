/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:03:27 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/29 10:48:06 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

int	textures_existance(t_textures *textures)
{
	if (!textures->no_texture)
		return (0);
	if (!textures->so_texture)
		return (0);
	if (!textures->we_texture)
		return (0);
	if (!textures->ea_texture)
		return (0);
	if (!textures->f_color)
		return (0);
	if (!textures->c_color)
		return (0);
	return (1);
}

int	parsing(char *path, t_data *data)
{
	char	*line;
	char	*map_str;
	int		fd;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (1);
	map_str = ft_strdup("");
	while (line)
	{
		if (textures_existance(data->textures) && ft_strchr(line, '1'))
			map_str = ft_strjoin(map_str, line);
		else
		{
			line = ft_strtrim(line, " ");
			parse_textures(line, data->textures);
		}
		line = get_next_line(fd);
	}
	close(fd);
	parse_map(map_str, data);

	// ..........Show allocated array
	for (int j = 0; j < 14; j++)
	{
		for (int k = 0; k < 33; k++)
			printf("%c", data->map[j][k]);
		printf("\n");
	}
	
	// .........Free 
	for (int j = 0; j < 14; j++)
	 	free(data->map[j]);
	free(map_str);
	free(data->map);
	
	return (0);
}
