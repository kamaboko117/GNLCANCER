/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/10 16:26:02 by asaboure          #+#    #+#             */
/*   Updated: 2020/02/25 16:24:57 by asaboure         ###   ########.fr       */
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
	while (str[i])
	{
		if (str[i] == '\n')
			return (1);
		i++;
	}
	return (0);
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

int		ft_freeresult(char **result, char **line, int i)
{
	if ((*line = ft_strdup_nl(*result)) == NULL)
		return (-1);
	if (*result)
		free(*result);
	return (i);
}

char	*ft_strjoin(char *s1, char const *s2)
{
	char	*ret;
	size_t	i;
	size_t	j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	if (!(ret = (char *)malloc(ft_strlen(s1) + ft_strlen(s2) + 1)))
		return (NULL);
	i = 0;
	while (s1[i])
	{
		ret[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j])
	{
		ret[i] = s2[j];
		i++;
		j++;
	}
	ret[i] = '\0';
	free(s1);
	return (ret);
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
		if ((i = read(fd, buf, BUFFER_SIZE)) == -1)
			return (-1);
		buf[i] = '\0';
		result = ft_strjoin(result, buf);
	}
	if ((i == 0) || i == -1)
		return (ft_freeresult(&result, line, i));
	*line = ft_strdup_nl(result);
	result = ft_next(result);
	if (result == NULL || line == NULL)
		return (-1);
	return (1);
}
