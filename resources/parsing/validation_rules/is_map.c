/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   is_map.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/05/11 08:31:24 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:08 by artemdanilo      ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../lib.h"

int	is_map(char *line)
{
	char	*str;

	str = skip_spaces(line);
	if (str[0] == '0' || str[0] == '1')
		return (1);
	if (ft_strchr("NSWE", str[0]))
	{
		if (str[1] && ft_isdigit(str[1]))
			return (1);
	}
	return (0);
}
