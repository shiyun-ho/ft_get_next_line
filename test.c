/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:25:13 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/19 20:08:21 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdio.h>
#include <fcntl.h>
#include <limits.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * Understanding how open() and read() works
 * Reads the file using read() function
*/
// int main()
// {
//     char *fileName = "hello.txt";
//     int fd = open(fileName, O_RDONLY);

//     if (fd == -1)
//     {
//         printf("Unable to read file. \n");
//         return 0;
//     } else{
//         printf("File was opened successfully! \n\n");
//     }

//     char buffer[5];

//     int bytesRead;
    
//     do {
//         bytesRead = read(fd, buffer, sizeof(buffer));
//         if (bytesRead > 0)
//         {
//             printf("%d bytes read! ", bytesRead); 
//             printf("File Contents: %s \n", buffer);
//         }
//     } while (bytesRead > 0);
                
//     if (bytesRead == -1)
//         printf("Error reading file. \n");

//     return 0;
// }



/**
 * cc -Wall -Wextra -Werror <files>.c
 * ./a.out sample.txt
 */
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

/**
 * dynamic version to test different inputs
*/
// int main(int argc, char* argv)
// {
//     int     fd;
//     char    *line;
    
//     if (argc != 2)
//     {
//         printf("No file or standard input text to read.\n");
//         return 0;
//     }
    
//     fd = open(argv[1], O_RDONLY);
    
//     if (fd == -1)
//     {
//         printf("Unable to read file. \n");
//         return 0;
//     } else{
//         printf("File was opened successfully! \n");
//     }
    
//     //TODO: Check if there is a need to check for NULL before printing
//     do{
//         line = get_next_line(fd); 
//         printf("%s", line); 
//         printf(" | ");
        
//         // if (line != NULL)
//         // {
//         //     printf("%s", line); 
//         //     printf(" | ");
//         // }
//     } while (line != NULL);
    
//     return (0);
// }