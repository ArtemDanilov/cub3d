/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_file.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/21 13:03:27 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/23 14:19:07 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

char	*get_texture_path(char *line)
{
	int	start;
	int	len;

	start = 3;
	len = ft_strlen(line) - start - 1;
	line = ft_substr(line, start, len);
	return (line);
}

int	parsing(char *path, t_textures *textures)
{
	char	*line;
	int		fd;

	fd = open(path, O_RDONLY);
	line = get_next_line(fd);
	if (!line)
		return (1);
	while (line)
	{
		line = ft_strtrim(line, " ");
		if (ft_strncmp(line, "NO", 2) == 0)
			textures->no_texture = get_texture_path(line);
		if (ft_strncmp(line, "SO", 2) == 0)
			textures->so_texture = get_texture_path(line);
		if (ft_strncmp(line, "WE", 2) == 0)
			textures->we_texture = get_texture_path(line);
		if (ft_strncmp(line, "EA", 2) == 0)
			textures->ea_texture = get_texture_path(line);
		line = get_next_line(fd);
	}
	return (0);
}
