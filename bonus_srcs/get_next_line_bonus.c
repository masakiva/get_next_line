/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mvidal-a <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/25 18:04:53 by mvidal-a          #+#    #+#             */
/*   Updated: 2019/11/26 16:32:36 by mvidal-a         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

t_list			*init_buffer(t_list *buf, int fd)
{
	buf = (t_list *)malloc(sizeof(t_list));
	if (buf != NULL)
	{
		buf->fd = fd;
		buf->rest = NULL;
		buf->status = NOT_FINISHED;
		buf->next = NULL;
	}
	return (buf);
}

static short	no_newline(char **line_part, t_list *b, char **line, size_t len)
{
	short		ret_code;

	ret_code = ERROR;
	if (b->status == NOT_FINISHED)
	{
		*line_part = strjoin_free(*line_part, b->rest, len, *line_part);
		free(b->rest);
		if (*line_part != NULL)
			ret_code = NOT_ENOUGH;
	}
	else
	{
		*line = strjoin_free(*line_part, b->rest, len, *line_part);
		if (*line != NULL)
			ret_code = END;
	}
	return (ret_code);
}

static short	parse_data(char **line_part, t_list *b, char **line, size_t len)
{
	short			ret_code;
	unsigned long	index;

	ret_code = ERROR;
	index = 0;
	while (index < len && (b->rest)[index] != '\n')
		index++;
	if (index < len)
	{
		*line = strjoin_free(*line_part, b->rest, index, *line_part);
		if (*line != NULL)
		{
			index++;
			b->rest = strjoin_free(NULL, b->rest + index, len - index, b->rest);
			if (b->rest != NULL)
				ret_code = ENOUGH;
			else
				free(*line);
		}
	}
	else
		ret_code = no_newline(line_part, b, line, len);
	return (ret_code);
}

static short	read_part(char **line_part, t_list *buf, char **line, int fd)
{
	short		ret_code;
	ssize_t		bytes_read;

	ret_code = NOT_ENOUGH;
	while (ret_code == NOT_ENOUGH)
	{
		ret_code = ERROR;
		buf->rest = (char *)malloc(sizeof(char) * BUFFER_SIZE);
		if (buf->rest != NULL)
		{
			bytes_read = read(fd, buf->rest, BUFFER_SIZE);
			if (fd != 0 && bytes_read < BUFFER_SIZE)
				buf->status = ALL_READ;
			else if (fd == 0
					&& (bytes_read == 0 || ((buf->rest)[bytes_read - 1] != '\n'
							&& bytes_read < BUFFER_SIZE)))
				buf->status = ALL_READ;
			if (bytes_read >= 0)
				ret_code = parse_data(line_part, buf, line, bytes_read);
		}
	}
	return (ret_code);
}

int				get_next_line(int fd, char **line)
{
	short			ret_code;
	static t_list	*buf = NULL;
	char			*line_part;
	t_list			*cur;

	ret_code = ERROR;
	if (line != NULL && fd >= 0 && BUFFER_SIZE > 0)
	{
		ret_code = NOT_ENOUGH;
		if (buf == NULL)
			if ((buf = init_buffer(buf, fd)) == NULL)
				ret_code = ERROR;
		cur = lstchr_fd(buf, fd);
		if (cur == NULL)
			ret_code = ERROR;
		line_part = NULL;
		if (cur->rest != NULL && ret_code != ERROR)
			ret_code = parse_data(&line_part, cur, line, ft_strlen(cur->rest));
		if (ret_code == NOT_ENOUGH)
			ret_code = read_part(&line_part, cur, line, fd);
		if (ret_code == END || ret_code == ERROR)
			lstrmone(&buf, fd);
	}
	return (ret_code);
}
