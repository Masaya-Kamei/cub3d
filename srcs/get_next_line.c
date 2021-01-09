/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/25 16:48:13 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/09 03:02:02 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	create_line(char **line, char **save)
{
	char *new_line_ptr;
	char *tmp;

	new_line_ptr = ft_strchr(*line, '\n');
	if (new_line_ptr == NULL)
		return (0);
	tmp = ft_substr(*line, 0, new_line_ptr - *line);
	if (tmp == NULL)
	{
		free(*line);
		return (-1);
	}
	*save = ft_substr(new_line_ptr + 1, 0, ft_strlen(new_line_ptr + 1));
	if (*save == NULL)
	{
		free(*line);
		free(tmp);
		return (-1);
	}
	free(*line);
	*line = tmp;
	return (1);
}

static int	read_until_include_nl(int fd, char **line)
{
	ssize_t	readsize;
	char	*tmp;
	char	*buf;

	if (ft_strchr(*line, '\n') != NULL)
		return (1);
	if (!(buf = malloc(sizeof(char) * (BUFFER_SIZE + 1))))
		return (-1);
	while ((readsize = read(fd, buf, BUFFER_SIZE)) > 0)
	{
		buf[readsize] = '\0';
		tmp = ft_strjoin(*line, buf);
		free(*line);
		*line = tmp;
		if (*line == NULL)
		{
			free(buf);
			return (-1);
		}
		if (ft_strchr(*line, '\n') != NULL)
			break ;
	}
	free(buf);
	return (readsize);
}

int			get_next_line(int fd, char **line, char **save)
{
	if (fd < 0 || fd >= 256 || line == NULL || BUFFER_SIZE <= 0)
		return (-1);
	if (*save == NULL)
	{
		if (!(*line = ft_strdup("")))
			return (-1);
	}
	else
	{
		*line = *save;
		*save = NULL;
	}
	if (read_until_include_nl(fd, line) == -1)
	{
		free(*line);
		return (-1);
	}
	return (create_line(line, save));
}
