/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:21:56 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/21 18:34:54 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <unistd.h>

/**
 * To check number of file descriptors available:
 *      ulimit -a
*/

/**
 * Algorithm: 
 * 1. Read the file line by line into a buffer. 
 * 2. Extract lines from the buffer. 
 * 
 * 1. Loop to read the file in chunks. 
 * 2. Append each chunk to buffer. 
 * 3. Scan buffer for newlines. 
 * 4. Extract the lines as you find them. 
 * 
 * Edge cases:
 * 1. File ends. 
 * 2. No newline character at end of buffer. 
 */

/**
 * @brief: Function that returns a line read from a file descriptor
 * @param: fd: The file descriptor to read from
 * @return: read line: correct behaviour
 * @return: NULL: if there is nothing else to read, or an error occurred
 * @allowed functions: read(), malloc(), free()
 */


/**
 * Note: 
 * Good to free memory of the old buffer as you allocate new memory for new buffer
 * Assign null ????
*/

//TODO: to remove once checked
# include <stdio.h>

char *get_next_line(int fd)
{
    char        *buffer_array;
    static char *stash;
    char        *line;
    ssize_t     bytes_read;
    
    //Error handling when user input of fd and buffer is invalid
    if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
        return (NULL);
        
    //allocate memory for buffer_array
    buffer_array = (char *)ft_calloc(BUFFER_SIZE, sizeof(char));
    if (!buffer_array)
        return (NULL);
        
    //start reading from file/stdin and duplicating to buffer_array
    //TODO: Need while() loop to keep reading the file
        //keep reading until line break OR end of line  
    bytes_read = read(fd, buffer_array, BUFFER_SIZE);

    //error handling if read fails + free() if fails
    if (bytes_read < 0)
    {
        free(buffer_array);
        return (NULL);
    }
    
    buffer_array[bytes_read] = '\0';
    
    //TODO: Error handling if fd has changed since last read - Qn - HOW DO YOU KNOW?
    
    //if buffer_array is updated successfully (bytes_read > 0) --> update stash
    stash = ft_strdup("");
    //TODO: Check for memleaks on valgrind - strjoin might not free automatically
    stash = ft_strjoin(stash, buffer_array);
    //Error handling if stash update fails
    if (!stash) {
        free(buffer_array);
        free(stash);
        return (NULL);
    }
    
    //if buffer contains \n or is at EOF (handle EOF later)
    //TODO: Handle EOF for buffer -- when read = 0
    char *matching_newline = ft_strchr(buffer_array, '\n');
        //if I could find \n in the buffer_array
    if (matching_newline != NULL)
    {
        //strchr returns pointer to where \n is in the char[]
        //I now know where in my pointer in buffer_array is \n
            //position [i] is where \n is found in BUFFER_SIZE elements
        int position_len = *matching_newline - *buffer_array;
        //copy from 0 to ith position in BUFFER_SIZE to line
            // buffer_array = [ab\ncde] === > line = [...][ab]
        //which also means that I can use this relative position to manipulate where it is
        line = ft_substr(buffer_array, 0, position_len);
        //now that i have handled line and ready to return
        //I will now dump stash part after position
        int remaining_len = ft_strlen(stash) - position_len;
        stash = ft_substr(stash, position_len, remaining_len);
    }
    
    //TODO: Uncomment this once line has been successfully managed
    // return (line);
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
