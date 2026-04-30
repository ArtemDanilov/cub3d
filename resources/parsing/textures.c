/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:17:19 by artemdanilo       #+#    #+#             */
/*   Updated: 2026/04/30 12:40:56 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

char	*get_texture_path(char *line)
{
	line += 3;
	line = skip_spaces(line);
	line[ft_strlen(line) - 1] = '\0';
	return (line);
}

int	get_color(char *color)
{
	int	hex;
	int	val;
	int	shift;

	hex = 0;
	shift = 16;
	color += 2;
	while (*color && shift >= 0)
	{
		val = 0;
		while (ft_isdigit(*color))
		{
			val = val * 10 + (*color - '0');
			color++;
		}
		hex |= (val << shift);
		shift -= 8;
		if (*color)
			color++;
	}
	return (hex);
}

void	parse_textures(char *line, t_textures *textures)
{
	if (ft_strncmp(line, "NO", 2) == 0)
		textures->no_texture = get_texture_path(line);
	if (ft_strncmp(line, "SO", 2) == 0)
		textures->so_texture = get_texture_path(line);
	if (ft_strncmp(line, "WE", 2) == 0)
		textures->we_texture = get_texture_path(line);
	if (ft_strncmp(line, "EA", 2) == 0)
		textures->ea_texture = get_texture_path(line);
	if (ft_strncmp(line, "F", 1) == 0)
		textures->f_color = get_color(line);
	if (ft_strncmp(line, "C", 1) == 0)
		textures->c_color = get_color(line);
}
