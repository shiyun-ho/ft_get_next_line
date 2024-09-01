/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:25:13 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/01 20:23:34 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

int main()
{
    int     fd;
    char    *line;
    
    fd = open("gnlTester/continuous.txt", O_RDONLY);
    
    if (fd == -1)
    {
        printf("Unable to read file. \n");
        return 0;
    } else {
        printf("File was opened successfully! \n");
    }

    // for (int i = 0; i < 2; i++)
    // {
    //     line = get_next_line(fd);
    //     printf("line: %s", line);
    //     free(line);
    // }
    // close(fd);
    // printf("Closed fd! \n");
    
    for (line = get_next_line(fd); line; line = get_next_line(fd))
    {
        printf("line: %s", line);
        free(line);
    }
    line = get_next_line(fd);
    free(line);
    close(fd);
    
    return (0);
}