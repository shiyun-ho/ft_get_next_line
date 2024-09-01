/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/01 21:32:56 by hshi-yun         ###   ########.fr       */
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
    int     stash_newline_index;
    char    *new;
    
    stash_newline_index = ft_strchr_index(*stash, '\n');
    if (stash_newline_index != -1)
    {
        *line = (char *)ft_calloc(1, sizeof(char));
        if (!*line)
        {
            // free_resources(stash, NULL, line);
            return (-1);
        }
        new = ft_strjoin(*line, *stash, 0, stash_newline_index);
        if (!new)
        {
            // free_resources(stash, NULL, line);
            return (-1);
        }
        *line = new;
        new = ft_strtrim(*stash, stash_newline_index + 1);
        if (!new)
        {
            // free_resources(stash, NULL, line);
            return (-1);
        }
        *stash = new;
        return (1);
    }
    return (0);
}

int    process_buffer(ssize_t bytes, char **buffer, char **stash, char **line)
{
    char    *new;
    
    if (bytes < 0)
        return (-1);
    if (bytes == 0)
    {
        if (!(*line))
        {
            if (*stash)
            {
                *line = (char *)ft_calloc(1, sizeof(char));
                if (!*line)
                {
                    // free_resources(stash, buffer, line);
                    return (-1);
                }
                new = ft_strjoin(*line, *stash, 0, ft_strlen(*stash) - 1);
                if (!new)
                {
                    // free_resources(stash, buffer, line);
                    return (-1);
                }
                *line = new;
                free_resources(stash, buffer, NULL);
                if (!*line || !*line[0])
                    return (free(*line), *line = NULL, 0);
                return (1);
            }
            return (free(*buffer), *buffer = NULL, 1);
        }
        else
            return (free(*buffer), *buffer = NULL, 0);
    }
    (*buffer)[bytes] = '\0';
    return (1);
}

int     process_line(char **buffer, char **stash, char **line)
{
    int     newline_index;
    int     stash_strlen;
    char    *new;

    newline_index = ft_strchr_index(*buffer, '\n');
    if (!(*stash))
        *stash = (char *)ft_calloc(1, sizeof(char));
    if (!(*stash))
    {
        // free_resources(stash, buffer, line);
        return (-1);
    }
    if (newline_index == -1)
    {
        new = ft_strjoin(*stash, *buffer, 0, BUFFER_SIZE - 1);
        if (!new)
            return (-1);
        *stash = new;
        return(free_resources(NULL, buffer, NULL), 0);
    }
    new = ft_strjoin(*stash, *buffer, 0, newline_index);
    if (!new)
        return (-1);
    *stash = new;
    *line = (char *)ft_calloc(1, sizeof(char));
    if (!(*line))
    {
        // free_resources(stash, buffer, line);
        return (-1);
    }
    stash_strlen = ft_strlen(*stash);
    new = ft_strjoin(*line, *stash, 0, (stash_strlen - 1));
    if (!new)
    {
        // free_resources(stash, buffer, line);
        return (-1);
    }
    *line = new;
    free_resources(stash, NULL, NULL);
    if ((*buffer)[newline_index + 1] != '\0')
    {
        *stash = (char *)ft_calloc(1, BUFFER_SIZE);
        if (!(*stash))
        {
            // free_resources(stash, buffer, line);
            return (-1);
        }
        int strlen = ft_strlen(*buffer);
        new = ft_strjoin(*stash, *buffer, newline_index + 1, (strlen - 1));
        if (!new)
        {
            // free_resources(stash, buffer, line);
            return (-1);
        }
        *stash = new;
    }
    return(free_resources(NULL, buffer, NULL), 1);
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
    static t_list          gnl;

    gnl.line = NULL;
    gnl.buffer = NULL;
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (free_resources(&gnl.stash, NULL, NULL), NULL);
    gnl.bytes_read = 1;
    while (gnl.bytes_read > 0)
    {
        if (gnl.stash)
        {
            gnl.stash_result = process_stash(&gnl.stash, &gnl.line);
            if (gnl.stash_result > 0)
                return (gnl.line);
            else if (gnl.stash_result == -1)
                return (free_resources(&gnl.stash, &gnl.buffer, &gnl.line), NULL);
        }
        // if (gnl.stash && gnl.stash_result)
        //     return (gnl.line);
        if (gnl.stash_result == -1)
        {
            free_resources(&gnl.stash, &gnl.buffer, &gnl.line);
            return (NULL);
        }
        gnl.buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        if (!gnl.buffer)
        {
            free_resources(&gnl.stash, &gnl.buffer, &gnl.line);
            return NULL;
        }
        gnl.bytes_read = read(fd, gnl.buffer, BUFFER_SIZE);
        gnl.buffer_result = process_buffer(gnl.bytes_read, &gnl.buffer, &gnl.stash, &gnl.line);
        if (gnl.buffer_result == -1)
        {
            free_resources(&gnl.stash, &gnl.buffer, &gnl.line);
            return (NULL);
        }
        // if (!gnl.buffer && gnl.buffer_result)
        if (!gnl.buffer)
        {
            if (gnl.buffer_result)
                return (gnl.line);
            free_resources(NULL, &gnl.buffer, NULL);
            return (NULL);
        }
        gnl.line_result = process_line(&gnl.buffer, &gnl.stash, &gnl.line);
        if (gnl.line_result == 1)
            return (gnl.line);
        if (gnl.line_result == -1)
        {
            free_resources(&gnl.stash, &gnl.buffer, &gnl.line);
            return (NULL);
        }
    }
    return (gnl.line);
}

