/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_v4.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:21:56 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/25 21:16:02 by hshi-yun         ###   ########.fr       */
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
//TODO: to remove once checked
//TODO: my first char in static char is LOST! NOOOOOOOO
/**
 * hello world!
 * am from School 42!
*/
# include <stdio.h>

char *get_next_line(int fd)
{
    ssize_t     bytes_read;
    char        *buffer_array;
    static char *stash;
    char        *line;

    line = NULL;
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
    {
        if (!stash)
            free(stash);
        stash = NULL;
        return (stash);
    }
    
    buffer_array = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        bytes_read = read(fd, buffer_array, BUFFER_SIZE);
    
        if (bytes_read < 0)
        {
            free(buffer_array);
            buffer_array = NULL;
            return (NULL);
        }
        buffer_array[bytes_read] =  '\0';
        
        if (!stash)
            stash = (char *)ft_calloc(1, sizeof(char));
        stash = ft_strjoin(stash, buffer_array, BUFFER_SIZE);
        if (!stash)
        {
            free(buffer_array);
            buffer_array = NULL;
            break;
        }
        
        //In second iteration, 'I' does not copy from stash
        int newline_position = ft_strchr_index(buffer_array, '\n');
        if (!line)
            line = (char *)ft_calloc(1, sizeof(char));
            //condition to check if it is the second line printed
            //this works only for FIRST iteration
        if (newline_position == NULL)
        {
            //this condition is not accurate cos it is applicable to all STASH 
            int line_iteration_check = ft_strlen(stash) % BUFFER_SIZE;
            //my stash already contains prev saved char
            if (line_iteration_check == 0)
                line = ft_strjoin(line, buffer_array, BUFFER_SIZE);
            else
                //TODO: i need to have a sep function to join start of stash with line and exit
                //OR a check that I exit 
                line = ft_strjoin(line, stash, ft_strlen(stash)); 
        }
    
        //if \n is found in BUFFER
        if (newline_position != NULL)
        {
            line = ft_strjoin(line, buffer_array, newline_position);
            if (!line)
            {
                free(buffer_array);
                free(stash);
                buffer_array = NULL;
                stash = NULL;
            }
            int elements_remaining_buffer = BUFFER_SIZE - newline_position - 1;
            newline_position = (ft_strlen(stash) - 1) - elements_remaining_buffer;
            trim_newline(stash, newline_position);
            free(buffer_array);
            buffer_array = NULL;
            break;
        }
    }
    return (line);
}
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>

int main() {
    int     fd;
    char    *line;

    fd = open("hello.txt", O_RDONLY);

    if (fd == -1) {
        printf("Unable to read file. \n");
        return 0;
    } else {
        printf("File was opened successfully! \n");
    }

    line = get_next_line(fd);
    while (line && ft_strlen(line) > 0) {
        printf("%s\n", line);
        free(line);
        line = get_next_line(fd);
    }

    close(fd);

    return (0);
}