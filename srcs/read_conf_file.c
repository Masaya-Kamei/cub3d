/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_conf_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:58 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/05 18:36:32 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	finish_reading_conf_file(t_data *d, int ret)
{
	close(d->fd);
	finish_program(d, ret);
}

static void	read_size_tex_color(t_data *d)
{
	char	*line;
	char	**str;
	int		gnl_flag;
	int		ret;

	gnl_flag = 1;
	while (d->win.width == NOT_READ || d->win.height == NOT_READ
		|| d->tex[NOUTH].img.img == NULL || d->tex[SOUTH].img.img == NULL
		|| d->tex[EAST].img.img == NULL || d->tex[WEST].img.img == NULL
		|| d->tex[SPRITE].img.img == NULL || d->stage.color[FLOOR] == NOT_READ
		|| d->stage.color[CEIL] == NOT_READ)
	{
		if (gnl_flag == 0)
			finish_reading_conf_file(d, NOT_ENOUGH_ELEMENT);
		if ((gnl_flag = get_next_line(d->fd, &line)) == -1)
			finish_reading_conf_file(d, GNL_ERROR);
		str = ft_split(line, ' ');
		free(line);
		if (str == NULL)
			finish_reading_conf_file(d, MALLOC_ERROR);
		ret = branch_size_tex_color(d, str);
		free_double_pointer(str);
		if (ret != SUCCESS)
			finish_reading_conf_file(d, ret);
	}
}

static void	finish_reading_map(t_data *d, char *line, t_list **lst, int ret)
{
	if (line != NULL)
		free(line);
	if (lst != NULL)
		ft_lstclear(lst, free);
	close(d->fd);
	finish_program(d, ret);
}

static void	read_map(t_data *d)
{
	t_list	*lst;
	char	*line;
	int		ret;
	int		gnl_flag;

	lst = NULL;
	gnl_flag = 1;
	while (gnl_flag != 0)
	{
		gnl_flag = get_next_line(d->fd, &line);
		if (gnl_flag == -1)
			finish_reading_map(d, NULL, &lst, GNL_ERROR);
		ret = check_characters_of_map_line(&d->player, line, ft_lstsize(lst));
		if (ret != SUCCESS)
			finish_reading_map(d, line, &lst, ret);
		ret = add_map_line_to_list(&lst, line);
		if (ret != SUCCESS)
			finish_reading_map(d, line, &lst, ret);
	}
	if (d->player.pos.x == NOT_READ)
		finish_reading_map(d, NULL, &lst, NOT_DETECTED_PLAYER);
	if ((ret = create_map_from_list(lst, &d->stage)) != SUCCESS)
		finish_reading_map(d, NULL, &lst, ret);
	if ((ret = check_closed_map(d->player, d->stage)) != SUCCESS)
		finish_reading_map(d, NULL, NULL, ret);
}

void		read_conf_file(t_data *d, char *conf_file)
{
	d->fd = open(conf_file, O_RDONLY);
	if (d->fd == -1)
	{
		write(2, "Error\n", 7);
		perror(conf_file);
		finish_program(d, FILE_OPEN_ERROR);
	}
	read_size_tex_color(d);
	read_map(d);
	close(d->fd);
}
