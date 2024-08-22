/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hshi-yun <hshi-yun@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 14:00:47 by hshi-yun          #+#    #+#             */
/*   Updated: 2024/08/21 17:52:14 by hshi-yun         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stddef.h>
#include "get_next_line.h"

void	*ft_memset(void *s, int c, size_t n)
{
	size_t			i;
	unsigned char	*ptr;

	i = 0;
	ptr = (unsigned char *)s;
	while (i < n)
	{
		ptr[i] = (unsigned char) c;
		i++;
	}
	return (s);
}

void	*ft_calloc(size_t n, size_t size)
{
	void	*ptr;
	size_t	total_size;

	total_size = n * size;
	if (size != 0 && total_size / size != n)
		return (NULL);
	ptr = malloc(total_size);
	if (!ptr)
		return (NULL);
	ft_memset(ptr, 0, total_size);
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
size_t	ft_strlcpy(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	return_len;

	i = 0;
	return_len = ft_strlen(src);
	if (size == 0)
		return (return_len);
	while (i < size - 1 && src[i] != '\0')
	{
		dst[i] = src[i];
		i++;
	}
	dst[i] = '\0';
	return (return_len);
}
size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	i;
	size_t	dst_len;
	size_t	src_len;
	size_t	remaining_len;

	dst_len = ft_strlen(dst);
	src_len = ft_strlen(src);
	if (size <= dst_len)
		return (size + src_len);
	if (size >= dst_len + 1)
	{
		i = 0;
		remaining_len = size - dst_len - 1;
		while (i < remaining_len && src[i] != '\0')
		{
			dst[dst_len + i] = src[i];
			i++;
		}
		dst[dst_len + i] = '\0';
	}
	return (dst_len + src_len);
}
char	*ft_strjoin(char const *s1, char const *s2)
{
	char			*s_new;
	unsigned int	s_size;

	s_size = ft_strlen(s1) + ft_strlen(s2) + 1;
	s_new = malloc((s_size) * (sizeof(char)));
	if (!s1 || !s2 || !s_new)
		return (NULL);
	ft_strlcpy(s_new, s1, ft_strlen(s1) + 1);
	ft_strlcat(s_new, s2, s_size);
	return (s_new);
}
char	*ft_strdup(const char *s)
{
	char	*s2;

	s2 = malloc((ft_strlen(s) + 1) * sizeof(char));
	if (!s2)
		return (NULL);
	ft_strlcpy(s2, s, ft_strlen(s) + 1);
	return (s2);
}
char	*ft_strchr(const char *s, int c)
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
			return ((char *)&s[i]);
		i++;
	}
	return (NULL);
}
char	*ft_substr(char const *s, unsigned int start, size_t len)
{
	char	*sub_str;
	size_t	str_len;

	str_len = ft_strlen(s);
	if (!s)
		return (NULL);
	if (start >= str_len)
		return (ft_strdup(""));
	else if (len > (str_len - start))
		len = str_len - start;
	sub_str = ft_calloc(len + 1, sizeof(char));
	if (!sub_str)
		return (NULL);
	ft_strlcpy(sub_str, s + start, len + 1);
	return (sub_str);
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