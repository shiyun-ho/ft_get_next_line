/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiyun <shiyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/03 00:37:00 by shiyun           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void	free_resources(char **stash, char **buffer, char **line)
{
	if (stash && *stash)
	{
		free(*stash);
		*stash = NULL;
	}
	if (buffer && *buffer)
	{
		free(*buffer);
		*buffer = NULL;
	}
	if (line && *line)
	{
		free(*line);
		*line = NULL;
	}
}

int	process_stash(char **stash, char **line)
{
	int	stash_newline_index;

	stash_newline_index = ft_strchr_index(*stash, '\n');
	if (stash_newline_index != -1)
	{
		*line = ft_calloc(1, sizeof(char));
		if (!*line)
			return (-1);
		*line = ft_strjoin(*line, *stash, 0, stash_newline_index);
		if (!*line)
			return (-1);
		*stash = ft_strtrim(*stash, stash_newline_index + 1);
		if (!*stash)
			return (-1);
		return (1);
	}
	return (0);
}

int	process_buffer(int fd, char **buffer, char **stash, char **line)
{
	ssize_t	bytes;

	*buffer = ft_calloc(BUFFER_SIZE + 1, sizeof(char));
	bytes = read(fd, *buffer, BUFFER_SIZE);
	if (bytes < 0)
		return (-1);
	if (bytes == 0)
	{
		if (!(*line) && (*stash))
		{
			*line = ft_calloc(1, sizeof(char));
			*line = ft_strjoin(*line, *stash, 0, ft_strlen(*stash) - 1);
			if (!line)
				return (-1);
			free_resources(stash, buffer, NULL);
			if (!*line || !*line[0])
				return (free(*line), *line = NULL, 0);
			return (1);
		}
		return (free(*buffer), *buffer = NULL, 0);
	}
	(*buffer)[bytes] = '\0';
	return (1);
}

int	process_line(char **buffer, char **stash, char **line)
{
	int	newline_index;
	int	stash_strlen;
	int	strlen;

	newline_index = ft_strchr_index(*buffer, '\n');
	if (!(*stash))
		*stash = ft_calloc(1, sizeof(char));
	if (newline_index == -1)
	{
		*stash = ft_strjoin(*stash, *buffer, 0, BUFFER_SIZE - 1);
		return (free_resources(NULL, buffer, NULL), 0);
	}
	*stash = ft_strjoin(*stash, *buffer, 0, newline_index);
	*line = ft_calloc(1, sizeof(char));
	stash_strlen = ft_strlen(*stash);
	*line = ft_strjoin(*line, *stash, 0, (stash_strlen - 1));
	free_resources(stash, NULL, NULL);
	if ((*buffer)[newline_index + 1] != '\0')
	{
		*stash = ft_calloc(1, BUFFER_SIZE);
		strlen = ft_strlen(*buffer);
		*stash = ft_strjoin(*stash, *buffer, newline_index + 1, (strlen - 1));
	}
	return (free_resources(NULL, buffer, NULL), 1);
}

/**
 * @brief: Function that returns a line read from a file descriptor
 * @param: fd: The file descriptor to read from
 * @return: read line: correct behaviour
 * @return: NULL: if there is nothing else to read, or an error occurred
 * @allowed functions: read(), malloc(), free()
*/
char	*get_next_line(int fd)
{
	static t_list	gnl;

	gnl.line = NULL;
	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (free_resources(&gnl.stash, NULL, NULL), NULL);
	while (1)
	{
		if (gnl.stash && process_stash(&gnl.stash, &gnl.line) > 0)
			return (gnl.line);
		gnl.buffer_res = process_buffer(fd, &gnl.buffer, &gnl.stash, &gnl.line);
		if (gnl.buffer_res == -1)
			return (free_resources(&gnl.stash, &gnl.buffer, &gnl.line), NULL);
		if (!gnl.buffer)
		{
			if (gnl.buffer_res)
				return (gnl.line);
			return (free_resources(&gnl.stash, &gnl.buffer, &gnl.line), NULL);
		}
		gnl.line_res = process_line(&gnl.buffer, &gnl.stash, &gnl.line);
		if (gnl.line_res == 1)
			return (gnl.line);
		if (gnl.line_res == -1)
			return (free_resources(&gnl.stash, &gnl.buffer, &gnl.line), NULL);
	}
	return (gnl.line);
}
