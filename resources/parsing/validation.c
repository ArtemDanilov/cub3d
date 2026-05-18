/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:26:50 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/18 14:18:03 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

void	array_of_textures(void **arr, t_textures *t)
{
	arr[0] = t->no_texture;
	arr[1] = t->so_texture;
	arr[2] = t->we_texture;
	arr[3] = t->ea_texture;
}

int	textures_validation(t_textures *t)
{
	void	*arr_t[4];
	int		i;

	i = 0;
	array_of_textures(arr_t, t);
	while (i < 4)
	{
		if (!is_texture_path_valid(arr_t[i]))
			return (0);
		i++;
	}
	return (1);
}

int	data_validation(t_data *data)
{
	int	is_valid;

	is_valid = 1;
	if (data->row_len == 0)
	{
		print_error("Map is missing");
		is_valid = 0;
	}
	if (!textures_validation(data->textures))
	{
		print_error("Texture path is missing or incorrect");
		is_valid = 0;
	}
	if (!data->textures->f_color || !data->textures->c_color)
	{
		print_error("Color is missing or incorrect");
		is_valid = 0;
	}
	if (data->textures->duplicates)
	{
		print_error("Duplicates found");
		is_valid = 0;
	}
	return (is_valid);
}
