/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:22:23 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/31 18:14:53 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 1
# endif

char    *get_next_line(int fd);
void	*ft_calloc(size_t n, size_t size);
int	    ft_strlen(const char *s);
char	*ft_strjoin(char *s1, char *s2, int start, int end);
int		ft_strchr_index(char *s, int c);
char	*ft_strtrim(char *s1, int start_position);

#endif