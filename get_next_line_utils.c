/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/21 13:46:56 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/24 20:43:15 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

size_t	ft_strlen(const char *str)
{
	size_t	len;

	len = 0;
	if (str != NULL)
	{
		while (str[len] != '\0')
			len++;
	}
	return (len);
}

char	*strjoin_free(char *line_part, char *buf, size_t len_buf, char *to_free)
{
	char			*new_part;
	size_t			len_line;
	unsigned long	i;
	unsigned long	j;

	len_line = ft_strlen(line_part);
	new_part = (char *)malloc(sizeof(char) * (len_line + len_buf + 1));
	if (new_part != NULL)
	{
		i = 0;
		while (i < len_line)
		{
			new_part[i] = line_part[i];
			i++;
		}
		j = 0;
		while (j < len_buf)
			new_part[i++] = buf[j++];
		new_part[i] = 0;
	}
	free(to_free);
	return (new_part);
}
