/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v10.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/29 19:24:53 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/29 20:29:42 by hshi-yun         ###   ########.fr       */
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
/**
 * strjoin, strlen, reset to zero, calloc, substr
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
        return (free(stash), stash = NULL, NULL);
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        /**
         * Read from buffer
         */
        buffer = ft_calloc(1, sizeof(char));
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        if (bytes_read < 0)
            return (free(buffer), buffer = NULL, NULL);
        //CASE: Reached end of file
            //To consider: What about circumstances where stash still have elements remaining
        if (bytes_read == 0)
        {
            /**
             * if stash exists when EOF is reached
             * => Check if \n exists
             * YES: 
             * 
             */    
            return (free(buffer), buffer = NULL, NULL);
        }
        buffer[bytes_read] = '\0';
        
        /**
         * Transfer to stash
         * 
         * Check buffer if \n exists
         * 
         * YES: Concat to stash from beginning till the (\n_index position)
         * => Strdup from stash to line
         * => Free stash, stash = NULL;
         * => Copy from buffer[\n_index + 1] till (BUFFER_SIZE - 1) to stash
         * => Free buffer, buffer = NULL;
         * => Return line
         * 
         * NO: strjoin as per usual
         */
        
    }
}
