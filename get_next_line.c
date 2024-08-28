/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/27 17:04:41 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/28 21:54:04 by hshi-yun         ###   ########.fr       */
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

    line = NULL;
    buffer = NULL;
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (free(stash), stash = NULL, NULL);
    
    bytes_read = 1;
    while (bytes_read > 0)
    {
        if (stash)
        {
            int stash_newline_index = ft_strchr_index(stash, '\n');
            
            //if \n is found in stash, place it in line
            if (stash_newline_index != -1)
            {
                line = (char *)ft_calloc(1, sizeof(char));
                line = ft_strjoin(line, stash, 0, stash_newline_index);
                // line = ft_strjoin(line, stash, 0, (ft_strlen(stash) - 1));
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
                break;
            }
            if (!line)
                return (free(buffer), buffer = NULL, line);
            else
                return NULL;
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
            line = ft_strjoin(line, stash, 0, (ft_strlen(stash) - 1));
            if (buffer[buffer_newline_index + 1] == '\0')
            {
                free(stash);
                stash = NULL;
            }
            else
            {
                stash = (char *)ft_calloc(1, BUFFER_SIZE);
                stash = ft_strjoin(stash, buffer, buffer_newline_index + 1, BUFFER_SIZE - 1);
            }
            free(buffer);
            buffer = NULL;
            break;
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

    // fd = open("hello_2.txt", O_RDONLY);
    fd = open("gnlTester/41_with_nl", O_RDWR);

    if (fd == -1) {
        printf(">>> Unable to read file. \n");
        return 0;
    } else {
        printf(">>> File was opened successfully! \n");
    }

    printf(">>>>>>>>>> line: |%s", get_next_line(fd));
    printf(">>>>>>>>>> line: |%s", get_next_line(fd));
    printf(">>>>>>>>>> line: |%s", get_next_line(fd));
    
    // printf(">>>>>>>>>> line: |%s", get_next_line(fd));
    // printf(">>>>>>>>>> line: |%s", get_next_line(fd));
    
    // // for (line = get_next_line(fd); line; line = get_next_line(fd))
    // {
    //     printf(">>>>>>>>>> line: |%s", line);
    //     printf("\n");
    //     free(line);
    // }
    close(fd);

    return (0);
}
