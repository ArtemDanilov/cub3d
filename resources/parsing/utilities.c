/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artemdanilov <artemdanilov@student.42.f    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/30 12:37:15 by adanilov          #+#    #+#             */
/*   Updated: 2026/05/13 14:28:15 by artemdanilo      ###   ########.fr       */
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

void	print_error(char *msg)
{
	// ENODATA         61	   /* No data available */
	// EINVAL          22      /* Invalid argument */
	// ENOTDIR         20      /* Not a directory */
	// ENOENT           2      /* No such file or directory */
	// ENOEXEC          8      /* Exec format error */
	// strerror(errcode)
	printf("%sERROR: %s%s\n", COLOR_RED, msg, COLOR_RESET);
}

char	*get_file_extension(char *path)
{
	size_t	len;
	size_t	i;

	if (!path || !ft_strchr(path, '.'))
		return ("");
	len = ft_strlen(path);
	i = 0;
	while (path[len - 1 - i] != '.')
		i++;
	path += len - i;
	return (path);
}
