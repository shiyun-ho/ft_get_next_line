/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/01 18:34:51 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

void  free_resources(char **stash, char **buffer, char **line)
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
int    process_stash(char **stash, char **line)
{
    int stash_newline_index;
    
    stash_newline_index = ft_strchr_index(*stash, '\n');
    //if \n found in stash
    if (stash_newline_index != -1)
    {
        *line = (char *)ft_calloc(1, sizeof(char));
        if (!*line)
            return (-1);
        *line = ft_strjoin(*line, *stash, 0, stash_newline_index);
        *stash = ft_strtrim(*stash, stash_newline_index + 1);
        return (1);
    }
    return (0);
}

int    process_buffer(ssize_t bytes, char **buffer, char **stash, char **line)
{
    if (bytes < 0)
        return (free_resources(buffer, stash, NULL), -1);
    if (bytes == 0)
    {
        if (!(*line))
        {
            if (*stash)
            {
                *line = (char *)ft_calloc(1, sizeof(char));
                *line = ft_strjoin(*line, *stash, 0, ft_strlen(*stash) - 1);
                free_resources(stash, buffer, NULL);
                if (!*line || !*line[0])
                    return (free(*line), *line = NULL, -1);
                return (1);
            }
            return (free(*buffer), *buffer = NULL, 1);
        }
        else
            return (-1);
    }
    (*buffer)[bytes] = '\0';
    return (1);
}

int     process_line(char **buffer, char **stash, char **line)
{
    int     newline_index;

    newline_index = ft_strchr_index(*buffer, '\n');
    if (!(*stash))
        *stash = (char *)ft_calloc(1, sizeof(char));
    if (newline_index == -1)
    {
        *stash = ft_strjoin(*stash, *buffer, 0, BUFFER_SIZE - 1);
        if (!(*stash))
        {
            free_resources(stash, buffer, NULL);
            return (-1);
        }
        free_resources(NULL, buffer, NULL);
        return (0);
    }
    else
    {
        *stash = ft_strjoin(*stash, *buffer, 0, newline_index);
        *line = (char *)ft_calloc(1, sizeof(char));
        int stash_strlen = ft_strlen(*stash);
        *line = ft_strjoin(*line, *stash, 0, (stash_strlen - 1));
        free_resources(stash, NULL, NULL);
        if ((*buffer)[newline_index + 1] != '\0')
        {
            *stash = (char *)ft_calloc(1, BUFFER_SIZE);
            int strlen = ft_strlen(*buffer);
            *stash = ft_strjoin(*stash, *buffer, newline_index + 1, (strlen - 1));
        }
        free_resources(NULL, buffer, NULL);
        // break; ==> return (line)
        return (1);
    }
}

/**
 * @brief: Function that returns a line read from a file descriptor
 * @param: fd: The file descriptor to read from
 * @return: read line: correct behaviour
 * @return: NULL: if there is nothing else to read, or an error occurred
 * @allowed functions: read(), malloc(), free()
*/
char    *get_next_line(int fd)
{
    ssize_t     bytes_read;
    char        *buffer;
    static char *stash;
    char        *line;

    line = NULL;
    buffer = NULL;
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (free_resources(&stash, NULL, NULL), NULL);
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        if (stash && process_stash(&stash, &line))
            return (line);
        
        buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        int buffer_result = process_buffer(bytes_read, &buffer, &stash, &line);
        if (buffer_result < 0)
            return (NULL);
        if (buffer_result == 1)
        {
            if (!buffer)
                return (line);
        }
        
        int line_result = process_line(&buffer, &stash, &line);
        if (line_result == 1)
            return (line);
        if (line_result == -1)
        {
            return (NULL);
        }
    }
    return (line);
}

