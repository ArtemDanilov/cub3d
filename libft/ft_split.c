/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: artem <artem@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/07 10:04:17 by artem             #+#    #+#             */
/*   Updated: 2025/01/09 10:52:16 by artem            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

int	ft_word_counter(char const *s, char c)
{
	int	words;
	int	is_word;

	words = 0;
	is_word = 0;
	while (*s)
	{
		if (*s != c)
		{
			if (!is_word)
				words++;
			is_word = 1;
		}
		else if (*s == c && is_word)
		{
			is_word = 0;
		}
		s++;
	}
	return (words);
}

void	**ft_stralloc(char const *s, char c, int words, char **arr)
{
	int		i;
	int		k;
	int		start;

	i = 0;
	k = 0;
	while (s[k] == c && s[k] != '\0')
		k++;
	while (i < words)
	{
		start = k;
		while (s[k] != c && s[k] != '\0')
			k++;
		arr[i] = ft_substr(s, start, k - start);
		if (!arr[i])
			free(arr);
		while (s[k] == c && s[k] != '\0')
			k++;
		i++;
	}
	arr[i] = NULL;
	return ((void *)arr);
}

char	**ft_split(char const *s, char c)
{
	char	**arr;
	int		words;

	if (!s)
		return (NULL);
	words = ft_word_counter(s, c);
	arr = (char **)malloc((words + 1) * sizeof(char *));
	ft_stralloc(s, c, words, arr);
	return (arr);
}
