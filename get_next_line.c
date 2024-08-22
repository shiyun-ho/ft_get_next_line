/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:21:56 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/22 20:33:38 by hshi-yun         ###   ########.fr       */
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
# include <stdio.h>

char *get_next_line(int fd)
{
    ssize_t     bytes_read;
    char        *buffer_array;
    static char *stash;
    char        *line;

    line = NULL;
//CASE: if @param is invalid
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
    {
        //TODO: Decide what to free ===> free stash()?
        free(stash);
        stash = NULL;
        return (stash);
    }
}
#include <fcntl.h>
#include <limits.h>
#include <stdlib.h>

int main()
{
    int     fd;
    char    *line;
    
    fd = open("hello.txt", O_RDONLY);
    
    if (fd == -1)
    {
        printf("Unable to read file. \n");
        return 0;
    } else {
        printf("File was opened successfully! \n");
    }

    do {
        line = get_next_line(fd);
        printf("%s | ", line); 
    } while (!line);
    
    close(fd);
    
    return (0);
}
