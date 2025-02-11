/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ylahssin <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/07 15:01:21 by ylahssin          #+#    #+#             */
/*   Updated: 2024/12/07 15:01:27 by ylahssin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

void	*ft_free(char **store)
{
	free(*store);
	*store = NULL;
	return (*store);
}

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	i;
	char	*result;

	if (nmemb != 0 && size > SIZE_MAX / nmemb)
		return (NULL);
	result = malloc(nmemb * size);
	if (!result)
		return (NULL);
	i = 0;
	while (i < (nmemb * size))
		result[i++] = 0;
	return (result);
}

int	ft_read_from_file(int fd, char *buffer, char **store)
{
	int		read_byte;
	char	*tmp;

	read_byte = read(fd, buffer, BUFFER_SIZE);
	if (read_byte <= 0)
		return (read_byte);
	buffer[read_byte] = '\0';
	tmp = ft_strjoin(*store, buffer);
	if (!tmp)
		return (-1);
	ft_free(store);
	return (*store = tmp, read_byte);
}

char	*ft_extract_line(char **store)
{
	char	*new_pos;
	char	*tmp;
	char	*line;

	if (!*store || !**store)
		return (NULL);
	new_pos = ft_strchr(*store, '\n');
	if (new_pos)
	{
		line = ft_substr(*store, 0, new_pos - *store + 1);
		if (!line)
			return (NULL);
		tmp = ft_strdup(*store + (new_pos - *store + 1));
		if (!tmp)
			return (ft_free(&line));
		ft_free(store);
		return (*store = tmp, line);
	}
	if (*store || **store)
	{
		line = ft_strdup(*store);
		return (ft_free(store), line);
	}
	return (NULL);
}

char	*get_next_line(int fd)
{
	static char		*store[OPEN_MAX];
	char			*buffer;
	char			*line;
	int				bytes_read;

	if (fd < 0 || BUFFER_SIZE <= 0 || BUFFER_SIZE >= 2147483647 || read(fd, 0,
			0) == -1)
		return (ft_free(&store[fd]));
	buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	if (!buffer)
		return (ft_free(&store[fd]));
	while (!ft_strchr(store[fd], '\n'))
	{
		bytes_read = ft_read_from_file(fd, buffer, &store[fd]);
		if (bytes_read == -1)
			return (free(buffer), ft_free(&store[fd]));
		else if (bytes_read == 0)
			break ;
	}
	free(buffer);
	line = ft_extract_line(&store[fd]);
	if (!line || !*line)
		return (ft_free(&store[fd]));
	return (line);
}
