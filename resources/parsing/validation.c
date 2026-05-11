/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:26:50 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/11 13:03:23 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

int	data_validation(t_data *data)
{
	int	is_valid;

	is_valid = 1;
	if (!textures_existance(data->textures))
	{
		print_error(ENODATA);
		is_valid = 0;
	}
	else if (data->row_len == 0)
	{
		print_error(ENODATA);
		is_valid = 0;
	}

	return (is_valid);
}
