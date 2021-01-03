/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_closed_map.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/20 13:11:29 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/03 17:51:14 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	flood_fill(char **room, int x, int y, int *flag)
{
	if (room[y][x] == 'w' || room[y][x] == '1' || *flag != SUCCESS)
		return ;
	if (room[y][x] == ' ')
	{
		*flag = DETECTED_SPACE_IN_MAP;
		return ;
	}
	if (room[y][x] == 'x')
	{
		*flag = NOT_SURROUNDED_WALL;
		return ;
	}
	room[y][x] = 'w';
	flood_fill(room, x, y + 1, flag);
	flood_fill(room, x - 1, y, flag);
	flood_fill(room, x, y - 1, flag);
	flood_fill(room, x + 1, y, flag);
}

static char	**create_room(char **map, int room_width, int room_height)
{
	char	**room;
	int		y;

	if (!(room = (char **)malloc(sizeof(char *) * (room_height + 1))))
		return (NULL);
	y = 0;
	while (y < room_height)
	{
		if (!(room[y] = (char *)malloc(sizeof(char) * (room_width + 1))))
		{
			free_double_pointer(room);
			return (NULL);
		}
		ft_memset(room[y], 'x', room_width);
		if (y > 0 && y < room_height - 1)
			ft_memcpy(room[y] + 1, map[y - 1], ft_strlen(map[y - 1]));
		room[y][room_width] = '\0';
		y++;
	}
	room[y] = NULL;
	return (room);
}

int			check_closed_map(t_player player, t_stage stage)
{
	char	**room;
	int		flag;

	room = create_room(stage.map, stage.width + 2, stage.height + 2);
	if (room == NULL)
		return (MALLOC_ERROR);
	flag = SUCCESS;
	flood_fill(room, (int)player.pos.x + 1, (int)player.pos.y + 1, &flag);
	free_double_pointer(room);
	return (flag);
}
