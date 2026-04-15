/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:20 by artem             #+#    #+#             */
/*   Updated: 2025/01/05 18:47:21 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memchr(const void *s, int c, size_t n)
{
	const unsigned char	*fs;
	size_t				i;

	fs = (const unsigned char *)s;
	i = 0;
	while (i < n)
	{
		if (fs[i] == (unsigned char)c)
			return ((void *)(fs + i));
		i++;
	}
	return (0);
}
