/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v11.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:24:53 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/29 20:54:33 by hshi-yun         ###   ########.fr       */
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

    if (fd < 0 || fd > 1024 || BUFFER_SIZE < 0)
        return (NULL);
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        buffer = ft_calloc(BUFFER_SIZE, sizeof(char));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        if (bytes_read < 0)
            return(free(buffer), buffer = NULL, NULL);
        buffer[bytes_read] = '\0';
        
        int buffer_newline_position = ft_strchr_index(buffer, '\n');
        //if I can't find \n in buffer
        if (buffer_newline_position == -1)
        {
            //Add buffer to stash
        }
        //else if I can find \n in the buffer
        else
        {
            //Add buffer to stash till \n position
        }
    }
    
}
