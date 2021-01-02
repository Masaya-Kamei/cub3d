/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:41:50 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/02 14:53:56 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	add_map_to_list(t_list **lst, char *line, int *map_end)
{
	t_list	*new;

	if (ft_strlen(line) == 0 && *lst == NULL)
		free(line);
	else
	{
		if (ft_strlen(line) == 0)
		{
			*map_end = 1;
			free(line);
		}
		else
		{
			if (*map_end == 1)
				return (NOT_END_MAP);
			if (!(new = ft_lstnew(line)))
				return (MALLOC_ERROR);
			ft_lstadd_back(lst, new);
		}
	}
	return (SUCCESS);
}

t_list		*add_map_lines_to_list(t_data *d, int fd)
{
	int		gnl_flag;
	char	*line;
	int		map_end;
	t_list	*lst;
	int		ret;

	gnl_flag = 1;
	map_end = 0;
	lst = NULL;
	while (gnl_flag != 0)
	{
		if ((gnl_flag = get_next_line(fd, &line)) == -1)
		{
			ft_lstclear(&lst, free);
			finish_reading_conf_file(d, fd, GNL_ERROR);
		}
		ret = add_map_to_list(&lst, line, &map_end);
		if (ret != SUCCESS)
		{
			free(line);
			ft_lstclear(&lst, free);
			finish_reading_conf_file(d, fd, ret);
		}
	}
	return (lst);
}

void		create_map_from_list(t_data *d, int fd, t_list *lst, t_stage *stage)
{
	t_list	*next;
	int		i;

	if ((stage->height = ft_lstsize(lst)) < 3)
	{
		ft_lstclear(&lst, free);
		finish_reading_conf_file(d, fd, SMALL_MAP);
	}
	if (!(stage->map = (char **)malloc(sizeof(char *) * (stage->height + 1))))
	{
		ft_lstclear(&lst, free);
		finish_reading_conf_file(d, fd, MALLOC_ERROR);
	}
	stage->width = 0;
	i = 0;
	while (lst != NULL)
	{
		stage->map[i] = lst->content;
		stage->width = MAX((int)ft_strlen(stage->map[i]), stage->width);
		i++;
		next = lst->next;
		free(lst);
		lst = next;
	}
	stage->map[i] = NULL;
}

static void	get_player_vectors(t_data *d, char dir, int x, int y)
{
	d->player.pos.x = x + 0.5;
	d->player.pos.y = y + 0.5;
	if (dir == 'N' || dir == 'S')
	{
		d->player.dir.x = 0;
		d->player.dir.y = (dir == 'N') ? -1 : 1;
	}
	else
	{
		d->player.dir.y = 0;
		d->player.dir.x = (dir == 'W') ? -1 : 1;
	}
	d->player.plane.x = -d->player.dir.y * tan(VIEW_ANGLE * PI / 180);
	d->player.plane.y = d->player.dir.x * tan(VIEW_ANGLE * PI / 180);
	d->stage.map[y][x] = '0';
}

void		check_characters_of_map(t_data *d, int fd, int *player_flag)
{
	int x;
	int y;

	y = 0;
	while (d->stage.map[y] != NULL)
	{
		x = 0;
		while (d->stage.map[y][x] != '\0')
		{
			if (d->stage.map[y][x] == 'N' || d->stage.map[y][x] == 'S'
				|| d->stage.map[y][x] == 'W' || d->stage.map[y][x] == 'E')
			{
				if (*player_flag == 1)
					finish_reading_conf_file(d, fd, PLAYER_DOUBLE);
				get_player_vectors(d, d->stage.map[y][x], x, y);
				*player_flag = 1;
			}
			else if (d->stage.map[y][x] != '0' && d->stage.map[y][x] != '1'
				&& d->stage.map[y][x] != '2' && d->stage.map[y][x] != ' ')
				finish_reading_conf_file(d, fd, INVALID_CHARACTER_IN_MAP);
			x++;
		}
		y++;
	}
}
