/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:00:47 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/25 19:54:54 by hshi-yun         ###   ########.fr       */
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
size_t	ft_strlen(const char *s)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		i++;
	}
	return (i);
}
char	*ft_strjoin(char const *s1, char const *s2, size_t size)
{
	char			*s_new;
	unsigned int	s_new_size;
	
	int s1_len = ft_strlen(s1);
	int s2_len = ft_strlen(s2);
	s_new_size = ft_strlen(s1) + ft_strlen(s2);
	s_new = ft_calloc(s_new_size, sizeof(char));
	
	//copy s1 to s_new
	int i = 0;
	if (ft_strlen(s1) > 0)
	{
		//s1 is STASH, which means it will keep looping
		while (i < ft_strlen(s1))
		{
			s_new[i] = s1[i];
			i++;
		}
	}
	int j = 0;
	while (j < size)
	{
		s_new[i + j] = s2[j];
		j++;
	}
	s_new[i + j] = '\0';
	//concatenate s1 and s2 to s_new : (stash + BUFFER)
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
	return (0);
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
		s1[i] = NULL;
	}
}
