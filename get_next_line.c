/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: joaopere <joaopere@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/11/16 15:11:44 by joaopere          #+#    #+#             */
/*   Updated: 2021/11/17 16:04:41 by joaopere         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

char	*ft_save(char *save)
{
	int		i;
	int		c;
	char	*s;

	i = 0;
	while (save[i] && save[i] != '\n')
		i++;
	if (!save[i])
	{
		free(save);
		return (NULL);
	}
	s = (char *)malloc(sizeof(char) * (ft_strlen(save) - i + 1));
	if (!s)
		return (NULL);
	i++;
	c = 0;
	while (save[i])
		s[c++] = save[i++];
	s[c] = '\0';
	free(save);
	return (s);
}

/*
* L22/23 -> While save[i] exists and its different from the newline (\n) i moves another position inside save;
* L24/25/26 -> If there's an error with save[i]frees the memory of save and returns null;
* L29 -> S is the memory allocation using malloc;
* L29 -> strlen -- find length of string;
* L30/31 -> If there's an error with s returns NULL;
* L34/35 -> Creates a copy of the saved line;
* L36 -> Puts the final character at the end of the line;
* L37 -> Frees the memory of save;
* L38 -> Returns the line copy.
*/

char	*ft_get_line(char *save)
{
	int		i;
	char	*s;

	i = 0;
	if (!save[i])
		return (NULL);
	while (save[i] && save[i] != '\n')
		i++;
	s = (char *)malloc(sizeof(char) * (i + 2));
	if (!s)
		return (NULL);
	i = 0;
	while (save[i] && save[i] != '\n')
	{
		s[i] = save[i];
		i++;
	}
	if (save[i] == '\n')
	{
		s[i] = save[i];
		i++;
	}
	s[i] = '\0';
	return (s);
}

/*
* L59/60 -> If there's an error with save returns NULL;
* L61/62 -> While save[i] exists and its different from the newline (\n) i moves another position inside save;
* L63 -> S is the memory allocation using malloc;
* L64/65 -> If there's an error with s returns NULL;
* L67/69/70 -> While save[i] exists and its different from the newline (\n), s[i] becames a copy of save[i] and i increments;
* L72/74/75 -> If save[i] equals to the newline (\n), s[i] receives a copy of the \n and i increments;
* L77 -> Last position at s becames '\0';
* L78 -> Returns the s;
*/

char	*ft_read_save(int fd, char *save)
{
	char	*buf;
	int		read_bytes;

	buf = malloc((BUFFER_SIZE + 1) * sizeof(char));
	if (!buf)
	{
		return (NULL);
	}
	read_bytes = 1;
	while (!ft_strchr(save, '\n') && read_bytes != 0)
	{
		read_bytes = read(fd, buf, BUFFER_SIZE);
		if (read_bytes == -1)
		{
			free(buf);
			return (NULL);
		}
		buf[read_bytes] = '\0';
		save = ft_strjoin(save, buf);
	}
	free(buf);
	return (save);
}

/*
* L97 -> buf is a memory allocated using malloc;
* L98/100 -> If there's an error with buf returns NULL;
* L103 -> While save it's not '\n' and read_bytes it's different of 0;
* L103 -> strchr -- locate character in string;
* L105 -> read_bytes equals the read of the file;
* L106/108/109 -> If the read gives an error, returns NULL;
* L111 -> Last space at buf equals to final character (\0);
* L112 -> save equals the join of the strings save and buf;
* L114 -> Frees the buf;
* L115 -> Returns the save.
*/

char	*get_next_line(int fd)
{
	char		*line;
	static char	*save;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		return (0);
	}
	save = ft_read_save(fd, save);
	if (!save)
	{
		return (NULL);
	}
	line = ft_get_line(save);
	save = ft_save(save);
	return (line);
}

/*
* L136/138 -> If there's an error with fd and BUFFER_SIZE returns 0;
* L140 -> save equals the join of the strings save and buf;
* L141/143 -> If there's an error with save returns NULL;
* L145 -> line equals the line;
*/
