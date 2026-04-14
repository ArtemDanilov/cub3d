/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: adanilov <adanilov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/04/14 14:03:31 by adanilov          #+#    #+#             */
/*   Updated: 2026/04/14 18:02:51 by adanilov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../lib.h"

char	*feel_the_line(int fd, char *left, char *buf)
{
	char		*tmp;
	ssize_t		buf_read;

	buf_read = 1;
	while (buf_read > 0)
	{
		buf_read = read(fd, buf, BUFFER_SIZE);
		if (buf_read == -1)
		{
			free(left);
			return (NULL);
		}
		else if (buf_read == 0)
			break ;
		buf[buf_read] = 0;
		if (!left)
			left = ft_strdup("");
		tmp = left;
		left = ft_strjoin(tmp, buf);
		free(tmp);
		tmp = NULL;
		if (ft_strchr(buf, '\n'))
			break ;
	}
	return (left);
}

char	*set_the_line(char *stash)
{
	char	*line;
	int		i;

	i = 0;
	while (stash[i] != '\0' && stash[i] != '\n')
		i++;
	if (stash[i] == 0)
		return (NULL);
	line = ft_substr(stash, i + 1, ft_strlen(stash) - i);
	if (*line == 0)
	{
		free(line);
		line = NULL;
	}
	stash[i + 1] = 0;
	return (line);
}

char	*get_next_line(int fd)
{
	char			*buf;
	char			*line;
	static char		*left;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		free(left);
		free(buf);
		left = NULL;
		buf = NULL;
		return (NULL);
	}
	if (!buf)
		return (NULL);
	line = feel_the_line(fd, left, buf);
	free(buf);
	buf = NULL;
	if (!line)
		return (NULL);
	left = set_the_line(line);
	return (line);
}
