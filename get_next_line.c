/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:23 by joaopere          #+#    #+#             */
/*   Updated: 2021/11/12 15:52:58 by joaopere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

static char	*ft_trim(char **s, char **buf, int len)
{
	char	*ln;
	char	*tmp;
	int		i;

	if (*s)
		i = ft_strlen(*s);
	else
		i = 0;
	ln = (char *)malloc(sizeof(char) * len + i + 1);
	if (!ln)
		return (0);
	ft_memcpy(ln, *s, i);
	ft_memcpy(ln + i, *buf, len);
	ln[len + i] = '\0';
	tmp = ft_strdup((*buf) + len);
	if (*s)
		free(*s);
	(*s) = tmp;
	return (ln);
}

/*
* L17 -> s = storage.
* L17 -> buf = buffer.
* L17 -> len = line size.
* L24 -> Allocates the length of the string to i.
* L27 -> ln = Allocated memory by malloc.
* L30 -> memcpy -- copy memory area.
* L31 -> memcpy -- copy memory area.
* L32 -> Puts final character at the end.
* L33 -> tmp = strdup -- save a copy of a string.
* L35 -> Frees *s memory.
* L36 -> *s = tmp = copy of a string.
* L37 -> Returns ln.
*/

static char	*ft_get(char **s, int len)
{
	char	*ln;
	char	*tmp;
	int		i;

	ln = (char *)malloc(sizeof(char) * (len + 1));
	if (!ln)
	{
		return (NULL);
	}
	i = 0;
	while (i != len)
	{
		ln[i] = (*s)[i];
		i++;
	}
	ln[i] = '\0';
	tmp = ft_strdup(*s + i);
	free(*s);
	(*s) = tmp;
	return (ln);
}

static char	*ft_main(char **s, char **buf, int i)
{
	char	*ln;
	char	*tmp;

	ln = NULL;
	if (i <= 0)
	{
		if (i == 0 && *s)
		{
			ln = (*s);
			(*s) = NULL;
		}
		return (ln);
	}
	(*buf)[i] = '\0';
	tmp = ft_strchr(*buf, '\n');
	if (tmp)
		ln = ft_trim(s, buf, (tmp - *buf) + 1);
	else
	{
		tmp = ft_strjoin(*s, *buf);
		if (*s)
			free(*s);
		*s = tmp;
	}
	return (ln);
}

char	*get_next_line(int fd)
{
	static char	*stor;
	char		*ln;
	char		*buf;
	int			a;

	if ((read(fd, 0, 0) == -1) || fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	a = 1;
	ln = NULL;
	buf = ft_strchr(stor, '\n');
	if (!buf)
	{
		buf = (char *)malloc(sizeof(char) * (BUFFER_SIZE + 1));
		if (!buf)
			return (0);
		while (ln == NULL && a > 0)
		{
			a = read(fd, buf, BUFFER_SIZE);
			ln = ft_main(&stor, &buf, a);
		}
		free(buf);
	}
	else
		ln = ft_get(&stor, (buf - stor) + 1);
	return (ln);
}
