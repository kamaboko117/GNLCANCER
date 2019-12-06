/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asaboure <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/05 17:42:44 by asaboure          #+#    #+#             */
/*   Updated: 2019/12/06 20:04:42 by asaboure         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include <stdlib.h>

size_t	ft_strlen(char *s)
{
	size_t	i;

	i = 0;
	while (s[i])
		i++;
	return (i);
}

char	*ft_strdupnl(char *s, size_t lim)
{
	size_t	i;
	char	*cpy;

	i = 0;
	while (s[i] && s[i] != '\n' && i < lim)
		i++;
	if (!((cpy = (char *)malloc(sizeof(char) * i + 1))))
		return (NULL);
	i = 0;
	while (s[i] && s[i] != '\n' && i < lim)
	{
		cpy[i] = s[i];
		i++;
	}
	cpy[i] = '\0';
	return (cpy);
}

size_t	ft_strlcat(char *dst, const char *src, size_t dstsize)
{
	size_t	i;
	size_t	j;
	size_t	dest_len;
	size_t	src_len;

	i = 0;
	dest_len = ft_strlen(dst);
	src_len = ft_strlen((char *)src);
	j = dest_len;
	if (dstsize < dest_len)
		return (dstsize + src_len);
	while (src[i] && j < dstsize - 1)
	{
		dst[j] = src[i];
		i++;
		j++;
	}
	dst[j] = '\0';
	return (src_len + dest_len);
}
