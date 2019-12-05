/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 16:36:51 by asaboure          #+#    #+#             */
/*   Updated: 2019/12/05 19:19:55 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>

int		get_next_line(int fd, char **line)
{
	static size_t	l;
	static char		buf[BUFFER_SIZE];
	size_t			j;
	static size_t	size;
	char			*newstr;

	j = l;
	if (l < size)
	{
		if (!(*line = ft_strdupnl(buf + j, size - j)))
			return (-1);
		j += ft_strlen(*line) + 1;
	}
	else
	{
		l = 0;
		j = l;
		if (!(size = read(fd, buf, BUFFER_SIZE)))
			return (0);
		if (j - l < size)
		{
			while (buf[j] == '\n')
				j++;
			if (!(*line = ft_strdupnl(buf + j, size - j)))
				return (-1);
			j += ft_strlen(*line) + 1;
		}
	}
	l = j;
	if (buf[j - 1] != '\n')
	{
		get_next_line(fd, &newstr);
		*line = ft_strjoin(*line, newstr);
		free(newstr);
	}
	return (1);
}
