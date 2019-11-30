/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:05:11 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/26 16:24:50 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

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
	int				fd;
	short			status;
	char			*rest;
	struct s_list	*next;
}				t_list;

size_t			ft_strlen(const char *str);
char			*strjoin_free(char *line_part,
		char *buf, size_t len_buf, char *to_free);
t_list			*init_buffer(t_list *buf, int fd);
void			ft_lstadd_back(t_list **alst, t_list *new);
t_list			*lstchr_fd(t_list *lst, int fd);
void			lstrmone(t_list **lst, int fd);
int				get_next_line(int fd, char **line);

#endif
