/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/11 14:41:07 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/25 17:32:39 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# define ERROR			-1
# define END			0
# define ENOUGH			1
# define NOT_ENOUGH		2
# define NOT_FINISHED	3
# define ALL_READ		4

# include <stdlib.h>
# include <sys/types.h>
# include <sys/uio.h>
# include <unistd.h>

typedef struct	s_list
{
	short			status;
	char			*rest;
}				t_buf;

int				get_next_line(int fd, char **line);
size_t			ft_strlen(const char *str);
char			*strjoin_free(char *line_part, char *buf,
		size_t len_buf, char *to_free);

#endif
