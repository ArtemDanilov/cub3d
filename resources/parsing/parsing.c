/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:03:27 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/11 13:03:31 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

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
	free(map_str);

	// ..........Show allocated array
	// for (int j = 0; j < 14; j++)
	// {
	// 	for (int k = 0; k < 33; k++)
	// 		printf("%c", data->map[j][k]);
	// 	printf("\n");
	// }
	
	return (0);
}
