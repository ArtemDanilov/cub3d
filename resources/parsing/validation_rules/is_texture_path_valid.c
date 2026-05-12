/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_texture_path_valid.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/12 12:50:36 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/12 15:59:26 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib.h"

int	is_texture_path_valid(char *path)
{
	char	*f_ext;

	f_ext = get_file_extension(path);
	if (!f_ext)
		return (0);
	if (ft_strncmp(f_ext, "xpm", 3) != 0)
		return (0);
	return (1);
}
