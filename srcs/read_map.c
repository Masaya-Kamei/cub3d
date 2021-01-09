/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_map.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/18 14:41:50 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/09 12:35:19 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	get_player_vectors(t_player *player, char dir, int x, int y)
{
	player->pos.x = x + 0.5;
	player->pos.y = y + 0.5;
	if (dir == 'N' || dir == 'S')
	{
		player->dir.x = 0;
		player->dir.y = (dir == 'N') ? -1 : 1;
	}
	else
	{
		player->dir.y = 0;
		player->dir.x = (dir == 'W') ? -1 : 1;
	}
	player->plane.x = -player->dir.y * tan(VIEW_ANGLE * PI / 180);
	player->plane.y = player->dir.x * tan(VIEW_ANGLE * PI / 180);
}

static int	check_characters_of_map_line(t_player *player, char *line, int y)
{
	int x;

	x = 0;
	while (line[x] != '\0')
	{
		if (line[x] == 'N' || line[x] == 'S'
			|| line[x] == 'W' || line[x] == 'E')
		{
			if (player->pos.x != NOT_READ)
				return (PLAYER_DOUBLE_READ);
			get_player_vectors(player, line[x], x, y);
			line[x] = '0';
		}
		else if (line[x] != '0' && line[x] != '1'
				&& line[x] != '2' && line[x] != ' ')
		{
			if (y == 0)
				return (INVALD_ELEMENT_OR_INVALID_CHARACTER);
			else
				return (INVALID_CHARACTER_IN_MAP);
		}
		x++;
	}
	return (SUCCESS);
}

int			add_map_line_to_list(t_player *player, t_list **lst, char *line)
{
	t_list		*new;
	static int	map_y = 0;
	int			ret;

	if (ft_strlen(line) == 0)
	{
		if (map_y > 0)
			map_y = MAP_END;
		free(line);
	}
	else
	{
		if (map_y == MAP_END)
			return (NOT_END_MAP);
		if (ft_strlen(line) > 100 || map_y > 100)
			return (TOO_BIG_MAP);
		ret = check_characters_of_map_line(player, line, map_y);
		if (ret != SUCCESS)
			return (ret);
		if (!(new = ft_lstnew(line)))
			return (MALLOC_ERROR);
		ft_lstadd_back(lst, new);
		map_y++;
	}
	return (SUCCESS);
}

int			create_map_from_list(t_list *lst, t_stage *stage)
{
	t_list	*next;
	int		i;

	stage->height = ft_lstsize(lst);
	if (!(stage->map = (char **)malloc(sizeof(char *) * (stage->height + 1))))
		return (MALLOC_ERROR);
	stage->width = 0;
	i = 0;
	while (lst != NULL)
	{
		stage->map[i] = lst->content;
		if ((int)ft_strlen(stage->map[i]) > stage->width)
			stage->width = (int)ft_strlen(stage->map[i]);
		i++;
		next = lst->next;
		free(lst);
		lst = next;
	}
	stage->map[i] = NULL;
	return (SUCCESS);
}
