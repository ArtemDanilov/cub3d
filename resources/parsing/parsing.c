/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:03:27 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/05 10:52:01 by adanilov         ###   ########.fr       */
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
	char	*tmp_map_str;
	int		fd;

	fd = open(path, O_RDONLY);
	map_str = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (textures_existance(data->textures) && ft_strchr(line, '1'))
		{
			tmp_map_str = map_str;
			map_str = ft_strjoin(tmp_map_str, line);
			free(tmp_map_str);
		}
		else
			parse_textures(skip_spaces(line), data->textures);
		free(line);
	}
	close(fd);
	parse_map(map_str, data);

	// ..........Show allocated array
	// for (int j = 0; j < 14; j++)
	// {
	// 	for (int k = 0; k < 33; k++)
	// 		printf("%c", data->map[j][k]);
	// 	printf("\n");
	// }
	
	// printf("%s\n", data->textures->ea_texture);
	// printf("%s\n", data->textures->so_texture);
	// printf("%d\n", data->textures->f_color);
	// printf("%d", data->textures->c_color);
	
	// .........Free
	free(map_str);
	
	return (0);
}
