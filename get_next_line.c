/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:26:02 by asaboure          #+#    #+#             */
/*   Updated: 2019/12/12 21:01:04 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>

#include <stdio.h>

int		is_nl(char *str)
{
	size_t	i;

	i = 0;
	while (str[i++])
		if (str[i] == '\n')
			return (1);
	return (0);
}

char	*ft_strdup(const char *s1)
{
	char	*ret;
	size_t	i;

	i = 0;
	while (s1[i])
		i++;
	if (!(ret = (char *)malloc(sizeof(char) * i + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	ret[i] = '\0';
	return (ret);
}

char	*ft_next(char *result)
{
	size_t	i;
	char	*tmp;

	i = 0;
	while (result[i] && result[i] != '\n')
		i++;
	if (!(tmp = ft_strdup(result + i + 1)))
		return (NULL);
	free(result);
	if (!(result = ft_strdup(tmp)))
		return (NULL);
	free(tmp);
	return (result);
}

int		ft_freeresult(char *result, int i)
{
	free(result);
	return (i);
}

int		get_next_line(int fd, char **line)
{
	static char	*result = NULL;
	char		buf[BUFFER_SIZE + 1];
	int			i;

	i = 1;
	if (result == NULL)
	{
		if (!(result = (char *)malloc(1)))
			return (-1);
		result[0] = '\0';
	}
	while (i > 0 && is_nl(result) == 0)
	{
		i = read(fd, buf, BUFFER_SIZE);
		buf[i] = '\0';
		ft_strlcat(result, buf, ft_strlen(result) + ft_strlen(buf) + 1);
	}
	if ((result[0] == '\0' && i == 0) || i == -1)
		return (ft_freeresult(result, i));
	*line = ft_strdup_nl(result);
	result = ft_next(result);
	if (result == NULL || line == NULL)
		return (-1);
	return (1);
}
