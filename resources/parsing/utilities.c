/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: marvin <marvin@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:37:15 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/06 12:24:59 by marvin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../lib.h"

char	*skip_spaces(char *str)
{
	while (*str == ' ')
		str++;
	return (str);
}

int	is_rgb(char *str)
{
	int	val;
	int	i;
	int	digits;

	if (!str)
		return (0);
	i = 0;
	while (i++ < 3)
	{
		val = 0;
		digits = 0;
		while (ft_isdigit(*str))
		{
			val = val * 10 + (*str++ - '0');
			digits++;
		}
		if (digits == 0 || val > 255)
			return (0);
		if (i < 3 && *str != ',')
			return (0);
		if (i < 3)
			str++;
	}
	return (*str == '\0' || *str == '\n');
}
