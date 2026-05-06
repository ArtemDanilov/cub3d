/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_mem.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 11:47:53 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/30 14:42:13 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->rows)
		free(data->map[i++]);
	free(data->map);
}

void	free_textures(t_textures *textures)
{
	free(textures->no_texture);
	free(textures->so_texture);
	free(textures->we_texture);
	free(textures->ea_texture);
	free(textures);
}
