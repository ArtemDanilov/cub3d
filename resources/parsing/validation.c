/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:26:50 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/12 17:35:57 by adanilov         ###   ########.fr       */
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
	int		is_valid;
	int		i;

	is_valid = 1;
	i = 0;
	array_of_textures(arr_t, t);
	while (i < 4 && is_valid)
	{
		// printf("%s\n", (char *)arr_t[i]);
		if (!arr_t[i])
		{
			print_error(ENODATA);
			// printf("Test 1: %s\n", (char *)arr_t[i]);
			is_valid = 0;
		}
		if (!is_texture_path_valid(arr_t[i]))
		{
			print_error(ENODATA);
			// printf("Test 2: %s\n", (char *)arr_t[i]);
			is_valid = 0;
		}
		i++;
	}
	return (is_valid);
}

int	data_validation(t_data *data)
{
	int	is_valid;
	
	is_valid = 1;
	if (data->row_len == 0)
	{
		print_error(ENODATA);
		printf("Test 3: %d\n", data->row_len);
		is_valid = 0;
	}
	is_valid = textures_validation(data->textures);
	
	return (is_valid);
}
