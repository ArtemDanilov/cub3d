/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures_existance.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:31:24 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/11 13:03:41 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib.h"

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
