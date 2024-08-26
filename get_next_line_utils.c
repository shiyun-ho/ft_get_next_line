/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:00:47 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/26 21:03:17 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total_size;
	size_t	i;

	total_size = n * size;
	if (size != 0 && total_size / size != n)
		return (NULL);

	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);

	i = 0;
	while (i < n)
	{
		((unsigned char *)ptr)[i] = 0;
		i++;
	}
	return (ptr);
}
int	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2, int size)
{
	char			*s_new;
	unsigned int	s_new_size;
	
	s_new_size = ft_strlen(s1) + ft_strlen(s2);
	s_new = ft_calloc(s_new_size + 1, sizeof(char));
	
	int i = 0;
	if (ft_strlen(s1) > 0)
	{
		while (i < ft_strlen(s1))
		{
			s_new[i] = s1[i];
			i++;
		}
	}
	int j = 0;
	//Error handling for when str joins buffer array to line
	/**
	 * line = ft_strjoin(line, buffer_array, newline_position);
	 * size = newline_position
	 * 		
	 */
	if (size < BUFFER_SIZE)
	{
		while (j < size)
		{
			s_new[i + j] = s2[j];
			j++;
		}
		s_new[i + j] = '\0';
	}
	else
	{
		while ((i + j) < s_new_size)
		{
			s_new[i + j] = s2[j];
			j++;
		}
		s_new[s_new_size] = '\0';
	}	
	free((char *)s1);
	return(s_new);
}
int		ft_strchr_index(const char *s, int c)
{
	int		i;
	int		len;
	char	character;

	i = 0;
	len = ft_strlen(s);
	character = (char)c;
	while (i <= len)
	{
		if (s[i] == character)
			return (i);
		i++;
	}
	return (-1);
}
void	trim_newline(char *s1, int position)
{
	int	i;
	int	start_position;
	int end_position;
	
	if (!s1)
		return;
	start_position = position + 1;
	end_position = ft_strlen(s1) - 1;
	i = 0;
	while (s1[i] != '\0')
	{
		while (start_position <= end_position)
		{
			s1[i] = s1[start_position];
			i++;
			start_position++;
		}
		s1[i] = '\0';
	}
}
