/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:29 by artem             #+#    #+#             */
/*   Updated: 2025/01/07 09:29:55 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	const unsigned char	*f_src;
	unsigned char		*f_dest;
	size_t				i;

	f_src = (const unsigned char *)src;
	f_dest = (unsigned char *)dest;
	if (f_dest == f_src || n == 0)
		return (dest);
	if (f_dest > f_src)
	{
		while (n-- > 0)
			f_dest[n] = f_src[n];
	}
	else
	{
		i = 0;
		while (i < n)
		{
			f_dest[i] = f_src[i];
			i++;
		}
	}
	return (f_dest);
}
