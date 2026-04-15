/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memcpy.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/05 18:47:26 by artem             #+#    #+#             */
/*   Updated: 2025/01/07 09:38:44 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memcpy(void *dest, const void *src, size_t n)
{
	const unsigned char		*f_src;
	unsigned char			*f_dest;
	size_t					i;

	f_src = (const unsigned char *)src;
	f_dest = (unsigned char *)dest;
	i = 0;
	while (i < n)
	{
		f_dest[i] = f_src[i];
		i++;
	}
	return (f_dest);
}
