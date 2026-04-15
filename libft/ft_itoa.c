/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/09 10:54:05 by artem             #+#    #+#             */
/*   Updated: 2025/01/09 14:20:55 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_num_count(int n)
{
	int	i;

	i = 0;
	if (n <= 0)
		i++;
	while (n != 0)
	{
		n /= 10;
		i++;
	}
	return (i);
}

void	ft_putstr(int n, int sign, int size, char *num)
{
	while (size > sign)
	{
		num[size - 1] = n % 10 + '0';
		n /= 10;
		size--;
	}
}

char	*ft_itoa(int n)
{
	char	*num;
	int		sign;
	int		size;

	sign = 0;
	size = ft_num_count(n);
	num = malloc((size + 1) * sizeof(char));
	if (!num)
		return (NULL);
	if (n == -2147483648)
	{
		num[0] = '-';
		num[1] = '2';
		n = 147483648;
		sign = 2;
	}
	if (n < 0)
	{
		num[0] = '-';
		sign = 1;
		n = -n;
	}
	ft_putstr(n, sign, size, num);
	num[size] = '\0';
	return (num);
}
