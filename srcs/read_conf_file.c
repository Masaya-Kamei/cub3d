/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conf_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:58 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/31 19:30:03 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		finish_reading_conf_file(t_data *d, int fd, int error_nbr)
{
	close(fd);
	finish_program(d, error_nbr);
}

static void	read_size_tex_color(t_data *d, int fd)
{
	char	*line;
	char	**str;
	char	read_flags[8];
	int		gnl_flag;
	int		ret;

	ft_memset(read_flags, '0', 8);
	gnl_flag = 1;
	while (ft_strncmp(read_flags, "11111111", 8) != 0)
	{
		if (gnl_flag == 0)
			finish_reading_conf_file(d, fd, NOT_ENOUGH_ELEMENT);
		if ((gnl_flag = get_next_line(fd, &line)) == -1)
			finish_reading_conf_file(d, fd, GNL_ERROR);
		if (!(str = ft_split(line, ' ')))
		{
			free(line);
			finish_reading_conf_file(d, fd, MALLOC_ERROR);
		}
		free(line);
		ret = branch_size_tex_color(d, str, read_flags);
		free_double_pointer(str);
		if (ret != SUCCESS)
			finish_reading_conf_file(d, fd, ret);
	}
}

static void	read_map(t_data *d, int fd)
{
	t_list	*lst;
	int		player_flag;

	lst = add_map_lines_to_list(d, fd);
	create_map_from_list(d, fd, lst, &d->stage);
	player_flag = 0;
	check_characters_of_map(d, fd, &player_flag);
	if (player_flag == 0)
		finish_reading_conf_file(d, fd, NOT_DETECTED_PLAYER);
	check_closed_map(d, fd, d->stage);
}

void		read_conf_file(t_data *d, char *conf_file)
{
	int		fd;

	fd = open(conf_file, O_RDONLY);
	if (fd == -1)
	{
		write(2, "Error\n", 7);
		perror(conf_file);
		finish_program(d, FILE_OPEN_ERROR);
	}
	read_size_tex_color(d, fd);
	read_map(d, fd);
	close(fd);
}
