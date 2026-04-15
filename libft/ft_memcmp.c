/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcmp.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:23 by artem             #+#    #+#             */
/*   Updated: 2025/01/05 18:47:24 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_memcmp(const void *s1, const void *s2, size_t n)
{
	const unsigned char	*fs1;
	const unsigned char	*fs2;
	size_t				i;

	fs1 = (const unsigned char *)s1;
	fs2 = (const unsigned char *)s2;
	i = 0;
	while (i < n)
	{
		if (fs1[i] != fs2[i])
			return ((int)(fs1[i] - fs2[i]));
		i++;
	}
	return (0);
}
