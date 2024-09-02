/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/31 18:35:30 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

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

    //initialise to NULL if line OR buffer was freed but ever set NULL
    line = NULL;
    buffer = NULL;
    //error handling for invalid param ===> free existing stash if exists
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (free(stash), stash = NULL, NULL);
    
    //initialise looping through the field
    bytes_read = 1;
    while (bytes_read > 0)
    {
        //if stash exists
        if (stash)
        {
            //check for where \n is found inside stash
            int stash_newline_index = ft_strchr_index(stash, '\n');
            
            //if \n is found in stash, place it in line
            if (stash_newline_index != -1)
            {
                line = (char *)ft_calloc(1, sizeof(char));
                line = ft_strjoin(line, stash, 0, stash_newline_index);
                stash = ft_strtrim(stash, stash_newline_index + 1);
                return (line);
            }
        }
        buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        //return NULL for both cases
        if (bytes_read < 0)
        {
            free(buffer);
            buffer = NULL;
            free(stash);
            stash = NULL;
            return NULL;
        }
        if (bytes_read == 0)
        {
            if (!line && stash)
            {
                line = (char *)ft_calloc(1, sizeof(char));
                line = ft_strjoin(line, stash, 0, ft_strlen(stash) - 1);
                free(stash);
                stash = NULL;
                free(buffer);
                buffer = NULL;
                if (!line || !line[0])
                {
                    free(line);
                    line = NULL;
                    return (NULL);
                }
                break;
            }
            if (!line)
            {
                return (free(buffer), buffer = NULL, line);
            }
            else
            {
                return NULL;
            }
        }
        buffer[bytes_read] = '\0';
        
        int buffer_newline_index = ft_strchr_index(buffer, '\n');
        if (!stash)
            stash = (char *)ft_calloc(1, sizeof(char));

//if newline not found in buffer
        if (buffer_newline_index == -1)
        {
            //keep adding buffer to stash
            stash = ft_strjoin(stash, buffer, 0, BUFFER_SIZE - 1);
            if (!stash)
                return (free(buffer), buffer = NULL, NULL);
            free(buffer);
            buffer = NULL;
        }
        //if newline is found in buffer
        else
        {
            //add to stash till the position where the index is
            stash = ft_strjoin(stash, buffer, 0, buffer_newline_index);
            line = (char *)ft_calloc(1, sizeof(char));
            int stash_strlen = ft_strlen(stash);
            line = ft_strjoin(line, stash, 0, (stash_strlen - 1));
            if (buffer[buffer_newline_index + 1] == '\0')
            {
                free(stash);
                stash = NULL;
            }
            else
            {
                free(stash);
                stash = NULL;
                stash = (char *)ft_calloc(1, BUFFER_SIZE);
                int buffer_strlen = ft_strlen(buffer);
                stash = ft_strjoin(stash, buffer, buffer_newline_index + 1, (buffer_strlen - 1));
            }
            free(buffer);
            buffer = NULL;
            break;
        }
    }
    return (line);
}
