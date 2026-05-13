/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:03:27 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:13 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

int	parsing(int fd, t_data *data)
{
	char	*line;
	char	*map_str;
	char	*tmp_map_str;

	map_str = ft_strdup("");
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		if (is_map(line))
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
	return (0);
}
