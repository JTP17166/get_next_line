/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopere <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/08 12:44:23 by joaopere          #+#    #+#             */
/*   Updated: 2021/11/11 16:56:01 by joaopere         ###   ########.fr       */
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

/*
* L15 -> Allocates len + 1 bytes and copies the string. 
* Merges storage with new line, 
* and stores the reminder of buf in storage.
* L23 -> strlen -- find length of string.
* L32 -> Returns 0 if there are no more bytes to read next time.
* L34 -> memcpy -- copy memory area.
* L35 -> memcpy -- copy memory area.
* L37 -> strdup -- save a copy of a string.
*
* L46 -> Allocared n bytes + 1 and copies the string. 
* Then updates the storage keeping the remainder.
* L64 -> strdup -- save a copy of a string.
*
* L70 -> Calls the functions and starts the program.
* L86 -> strchr -- locate character in string.
* L89 -> Allocates and copies the string.
* L93 -> Allocates (with malloc(3)) and returns a new
* string, which is the result of the concatenation
* of ’s1’ and ’s2’.
*
* L103 -> Looks for a new line in storage.
* L116 -> strchr -- locate character in string.
* L127 -> Calls the functions and starts the program.
* L133 -> Allocared n bytes + 1 and copies the string. 
*/
