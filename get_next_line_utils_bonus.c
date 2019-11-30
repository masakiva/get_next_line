/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:04:32 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/26 16:31:25 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

void	lstrmone(t_list **lst, int fd)
{
	t_list	*before;
	t_list	*after;

	if (*lst != NULL && (*lst)->fd == fd)
	{
		after = (*lst)->next;
		free((*lst)->rest);
		free(*lst);
		*lst = after;
	}
	else if ((before = *lst) != NULL)
	{
		while (before->next != NULL)
		{
			if (before->next->fd == fd)
			{
				after = before->next->next;
				free(before->next->rest);
				free(before->next);
				before->next = after;
				break ;
			}
			before = before->next;
		}
	}
}

void	ft_lstadd_back(t_list **alst, t_list *new)
{
	t_list	*last;

	if (*alst != NULL)
	{
		last = *alst;
		while (last != NULL && last->next != NULL)
			last = last->next;
		last->next = new;
	}
	else
		*alst = new;
}

t_list	*lstchr_fd(t_list *lst, int fd)
{
	t_list	*first;
	t_list	*accur;

	accur = NULL;
	first = lst;
	while (lst != NULL)
	{
		if (lst->fd == fd)
			accur = lst;
		lst = lst->next;
	}
	if (accur == NULL)
	{
		accur = init_buffer(accur, fd);
		if (accur != NULL)
			ft_lstadd_back(&first, accur);
	}
	return (accur);
}
