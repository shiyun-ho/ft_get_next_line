/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:00:47 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/09/01 17:23:51 by hshi-yun         ###   ########.fr       */
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
char	*ft_strjoin(char *s1, char *s2, int start_position, int end_position)
{
	char			*s3;
	unsigned int	s3_size;
	int				s1_len;
	int				i;

	s1_len = ft_strlen(s1);
	s3_size = s1_len + (end_position - start_position + 1);
	s3 = ft_calloc(s3_size + 1, sizeof(char));
	
	i = 0;
	while (i < s1_len)
	{
		s3[i] = s1[i];
		i++;
	}
	while (start_position <= end_position)
	{
		s3[i] = s2[start_position];
		i++;
		start_position++;	
	}
	s3[s3_size] = '\0';
	free(s1);
	return (s3);
}
int		ft_strchr_index(char *s, int c)
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
char	*ft_strtrim(char *s1, int start_position)
{
	char	*str;
	int		s1_len;
	int		end_position;
	int		i;
	
	s1_len = ft_strlen(s1);
	end_position = s1_len - 1;

	str = ft_calloc((end_position - start_position + 1 + 1), sizeof(char));
	if (!str)
		return (free(s1), NULL);
	if (str)
	{
		i = 0;
		while(start_position <= end_position)
		{
			str[i] = s1[start_position];
			start_position++;
			i++;
		}
		str[i] = '\0';		
	}
	free(s1);
	s1 = NULL;
	return (str);
}
