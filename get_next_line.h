/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/18 17:22:23 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/24 20:17:17 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

#include <stdlib.h>
#include <stddef.h>

#ifndef BUFFER_SIZE
# define BUFFER_SIZE 5
# endif

char    *get_next_line(int fd);
void    *ft_calloc(size_t n, size_t size);
size_t	ft_strlen(const char *s);
char	*ft_strjoin(char const *s1, char const *s2, size_t size);
int		ft_strchr_index(const char *s, int c);

#endif