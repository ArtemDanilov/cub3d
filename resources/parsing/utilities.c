/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:37:15 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/11 13:03:09 by artemdanilo      ###   ########.fr       */
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

void	print_error(int	errcode)
{
	// ENODATA         61	   /* No data available */
	// EINVAL          22      /* Invalid argument */
	// ENOTDIR         20      /* Not a directory */
	// ENOENT           2      /* No such file or directory */
	printf("ERROR: %s\n", strerror(errcode));
}
