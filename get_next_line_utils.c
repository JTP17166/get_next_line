/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/05 14:57:07 by joaopere          #+#    #+#             */
/*   Updated: 2021/11/12 12:40:45 by joaopere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	int		i;
	char	*c;

	i = 0;
	c = (char *)(s);
	while (c && *c)
	{
		c++;
		i++;
	}
	return (i);
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	size_t	i;
	size_t	s1l;
	size_t	s2l;
	char	*ptr;

	i = 0;
	ptr = NULL;
	if (!s1 && !s2)
		return (NULL);
	if (s1 && !s2)
		return (ft_strdup(s1));
	else if (!s1 && s2)
		return (ft_strdup(s2));
	s1l = ft_strlen(s1);
	s2l = ft_strlen(s2);
	ptr = (char *)malloc(sizeof(char) * (s1l + s2l + 1));
	if (!ptr)
		return (NULL);
	while (i < (s1l + s2l + 1))
		ptr[i++] = 0;
	ft_memcpy(ptr, s1, s1l);
	ft_memcpy(ptr + s1l, s2, s2l);
	ptr[s1l + s2l] = '\0';
	return (ptr);
}

void	*ft_memcpy(void *dst, const void *src, size_t n)
{
	char	*dstptr;
	char	*srcptr;

	dstptr = (char *)(dst);
	srcptr = (char *)(src);
	if (dstptr && srcptr)
	{
		while (n--)
		{
			*dstptr++ = *srcptr++;
		}
	}
	return ((void *)dst);
}

char	*ft_strdup(const char *s)
{
	char	*str;
	int		len;

	if (s)
	{
		len = ft_strlen(s);
		if (!len)
		{
			return (NULL);
		}
		str = (char *)malloc(sizeof(char) * (len + 1));
		if (!str)
		{
			return (NULL);
		}
		ft_memcpy(str, s, len);
		*(str + len) = '\0';
		return (str);
	}
	return (NULL);
}

char	*ft_strchr(const char *s, int c)
{
	char	*tmp;

	if (s)
	{
		tmp = (char *)(s);
		while (*tmp)
		{
			if (*tmp == (char)c)
				return (tmp);
			tmp++;
		}
		if (*tmp == c)
			return (tmp);
	}
	return (NULL);
}
