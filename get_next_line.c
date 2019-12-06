/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:36:51 by asaboure          #+#    #+#             */
/*   Updated: 2019/12/06 19:52:49 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		get_line(char *buf, size_t j, size_t size, char **line)
{
	if (!(*line = ft_strdupnl(buf + j, size - j)))
		return (-1);
	j += ft_strlen(*line) + 1;
	return (j);
}

int		get_next_line(int fd, char **line)
{
	static size_t	l;
	static char		buf[BUFFER_SIZE];
	int				j;
	static size_t	size;
	char			*newstr;

	j = l;
	if (l < size)
		j = get_line(buf, j, size, line);
	else
	{
		l = 0;
		j = l;
		if (!(size = read(fd, buf, BUFFER_SIZE)))
			return (0);
		(j - l < size) ? j = get_line(buf, j, size, line) : 0;
	}
	(j != -1) ? l = j : 0;
	if (j != -1 && buf[j - 1] != '\n')
	{
		get_next_line(fd, &newstr);
		ft_strlcat(*line, newstr, ft_strlen(*line) + ft_strlen(newstr));
		free(newstr);
	}
	return ((j != -1) ? 1 : -1);
}
