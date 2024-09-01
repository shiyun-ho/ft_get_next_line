/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: shiyun <shiyun@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/01 00:53:42 by shiyun           ###   ########.fr       */
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
    //if \n not found in stash
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

char    *process_buffer(ssize_t bytes, char **buffer, char **stash, char **line)
{
    if (bytes < 0)
        // return (free_resources(&buffer, &stash, NULL), NULL);
        return (free_resources(buffer, stash, NULL), NULL);
    if (bytes == 0)
    {
        if (!line)
        {
            if (stash)
            {
                *line = (char *)ft_calloc(1, sizeof(char));
                *line = ft_strjoin(*line, *stash, 0, ft_strlen(*stash) - 1);
                free_resources(stash, buffer, NULL);
                if (!line || !line[0])
                    return (free(line), line = NULL, NULL);
                return (*line);
            }
            free_resources(NULL, buffer, NULL);
            return (*line);   
        }
        else
            return (NULL);
    }
    *buffer[bytes] = '\0';
    return (*buffer);
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

        // if (bytes_read < 0)
        //     return (free_resources(&buffer, &stash, NULL), NULL);
        // if (bytes_read == 0)
        // {
        //     if (!line)
        //     {
        //         if (stash)
        //         {
        //             line = (char *)ft_calloc(1, sizeof(char));
        //             line = ft_strjoin(line, stash, 0, ft_strlen(stash) - 1);
        //             free_resources(&stash, &buffer, NULL);
        //             if (!line || !line[0])
        //                 return (free(line), line = NULL, NULL);
        //             break;
        //         }
        //         return (free(buffer), buffer = NULL, line);   
        //     }
        //     else
        //         return (NULL);
        // }
        // buffer[bytes_read] = '\0';
        //TODO: Resolve!
        line = process_buffer(bytes_read, &buffer, &stash, &line);
        
        //process_to_line(char **buffer, char **stash, char **line)
        int buffer_newline_index = ft_strchr_index(buffer, '\n');
        if (!stash)
            stash = (char *)ft_calloc(1, sizeof(char));

        if (buffer_newline_index == -1)
        {
            stash = ft_strjoin(stash, buffer, 0, BUFFER_SIZE - 1);
            if (!stash)
                return (free(buffer), buffer = NULL, NULL);
            free_resources(NULL, &buffer, NULL);
        }
        else
        {
            stash = ft_strjoin(stash, buffer, 0, buffer_newline_index);
            line = (char *)ft_calloc(1, sizeof(char));
            int stash_strlen = ft_strlen(stash);
            line = ft_strjoin(line, stash, 0, (stash_strlen - 1));
            free_resources(&stash, NULL, NULL);
            if (buffer[buffer_newline_index + 1] != '\0')
            {
                stash = (char *)ft_calloc(1, BUFFER_SIZE);
                int buffer_strlen = ft_strlen(buffer);
                stash = ft_strjoin(stash, buffer, buffer_newline_index + 1, (buffer_strlen - 1));
            }
            free_resources(NULL, &buffer, NULL);
            break;
        }
    }
    return (line);
}

