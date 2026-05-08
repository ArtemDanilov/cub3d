/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/28 13:10:36 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/30 14:45:54 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "raycaster.h"

void	fill_map_array(char **map, char *map_str, int rows, int row_len)
{
	int	i;
	int	j;

	i = 0;
	while (i < rows)
	{
		map[i] = malloc((row_len + 1) * sizeof(char));
		j = 0;
		while (map_str[j] != '\n')
		{
			if (map_str[j] == ' ')
				map[i][j] = '1';
			else
				map[i][j] = map_str[j];
			j++;
		}
		map_str += j + 1;
		while (j < row_len)
		{
			map[i][j] = '1';
			j++;
		}
		map[i][j] = '\0';
		i++;
	}
}

void	count_map(char *map_str, t_data *data)
{
	int	cur_len;
	int	i;

	data->row_len = 0;
	data->rows = 0;
	cur_len = 0;
	i = 0;
	while (map_str[i])
	{
		if (map_str[i] == '\n')
		{
			if (cur_len > data->row_len)
				data->row_len = cur_len;
			cur_len = 0;
			data->rows++;
		}
		else
			cur_len++;
		i++;
	}
}

void	parse_map(char *map_str, t_data *data)
{
	count_map(map_str, data);
	data->map = malloc(data->rows * sizeof(char *));
	if (!data->map)
		return ;
	fill_map_array(data->map, map_str, data->rows, data->row_len);
}
