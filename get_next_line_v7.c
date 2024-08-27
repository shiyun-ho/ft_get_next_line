/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v7.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/27 22:22:18 by hshi-yun         ###   ########.fr       */
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
#include <stdio.h>

char    *get_next_line(int fd)
{
    ssize_t     bytes_read;
    char        *buffer;
    static char *stash;
    char        *line;

    line = NULL;
    //Handle invalid user input and param
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (free(stash), stash = NULL, NULL);
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        buffer = (char *)ft_calloc(BUFFER_SIZE + 1, sizeof(char));
        //Allocate buffer with read characters of the size BUFFER
        bytes_read = read(fd, buffer, BUFFER_SIZE);
        
        if (bytes_read <= 0)
            return (free(buffer), buffer = NULL, line);
        buffer[bytes_read] = '\0';
        
//CASE: Check for \n before adding to stash
        int newline_index = ft_strchr_index(buffer, '\n');
        if (!stash)
            stash = (char *)ft_calloc(1, sizeof(char));
        if (newline_index == -1)
        {
            //Allocate stash by joining stash "" with buffer[abcde]
            stash = ft_strjoin(stash, buffer, 0, BUFFER_SIZE - 1);
            if (!stash)
                return (free(buffer), buffer = NULL, NULL);
            
            //Allocate line by joining buffer to existing line
                //CASE 1: if \n is not detected in buffer
                //CASE 2: if \n is detected in buffer
                //CASE 3: if stash retains from previous line read (NOT RESOLVED)
            if (!line)
                line = (char *)ft_calloc(1, sizeof(char));
            //TODO: Mechanism to detect if '\n' is detected
            
            int check_iteration = ft_strlen(stash) % BUFFER_SIZE;
            int check_subsequent = ft_strlen(stash) / BUFFER_SIZE;
            //if my stash contains values from previous line buffer
            if (check_iteration > 0 && check_subsequent > 1)
                line = ft_strjoin(line, stash, 0, ft_strlen(stash) - 1);
            else
                line = ft_strjoin(line, buffer, 0, BUFFER_SIZE - 1);
        }
        else
        {
            if (newline_index == 0)
            {
                free(stash);
                stash = (char *)ft_calloc(1, BUFFER_SIZE);
                stash = ft_strjoin(stash, buffer, newline_index + 1, BUFFER_SIZE - 1);
                free(buffer);
                buffer = NULL;
            }
            else
            {
                free(stash);
                stash = (char *)ft_calloc(1, BUFFER_SIZE);
                //STASH retains, need to think about how to add to next line
                stash = ft_strjoin(stash, buffer, newline_index + 1, BUFFER_SIZE - 1);
                line = ft_strjoin(line, buffer, 0, newline_index - 1);
                free(buffer);
                buffer = NULL;
            }
            return (line);
        }
    }
    return (line);
}
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>
#include <stdio.h>

int main() {
    int     fd;
    char    *line;

    fd = open("hello.txt", O_RDONLY);

    if (fd == -1) {
        printf(">>> Unable to read file. \n");
        return 0;
    } else {
        printf(">>> File was opened successfully! \n");
    }

    for (line = get_next_line(fd); line; line = get_next_line(fd))
    {
        printf("| line: %s |", line);
        printf("\n=== Free (line) ===\n");
        free(line);
    }
    close(fd);

    return (0);
}
