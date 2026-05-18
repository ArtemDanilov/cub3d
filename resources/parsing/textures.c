/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/25 11:17:19 by artemdanilo       #+#    #+#             */
/*   Updated: 2026/05/18 13:21:45 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

char	*get_texture_path(char *line)
{
	char	*start;
	char	*path;
	int		len;

	if (!line)
		return (NULL);
	line += 3;
	start = skip_spaces(line);
	len = ft_strlen(start);
	if (len > 0 && start[len - 1] == '\n')
		len--;
	// Handle whitespaces from right
	path = ft_substr(start, 0, len);
	return (path);
}

int	get_color(char *color)
{
	int	hex;
	int	val;
	int	shift;

	hex = 0;
	shift = 16;
	color += 2;
	color = skip_spaces(color);
	if (!is_rgb(color))
		return (0);
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
	static char		seen[256];
	char			c;

	c = line[0];
	if (seen[(int)c] == c)
		textures->duplicates = 1;
	if (ft_strncmp(line, "NO ", 3) == 0)
		textures->no_texture = get_texture_path(line);
	else if (ft_strncmp(line, "SO ", 3) == 0)
		textures->so_texture = get_texture_path(line);
	else if (ft_strncmp(line, "WE ", 3) == 0)
		textures->we_texture = get_texture_path(line);
	else if (ft_strncmp(line, "EA ", 3) == 0)
		textures->ea_texture = get_texture_path(line);
	else if (ft_strncmp(line, "F", 1) == 0)
		textures->f_color = get_color(line);
	else if (ft_strncmp(line, "C", 1) == 0)
		textures->c_color = get_color(line);
	if (c != '\0' && c != '\n')
		seen[(int)c] = c;
}
