/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deal_key.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/15 16:08:20 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/31 19:27:12 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static void	move_y_player(t_player *p, char **map, int key)
{
	double	move;
	double	destination;

	move = MOVE;
	if (key == S_KEY || key == A_KEY)
		move *= -1;
	if (key == W_KEY || key == S_KEY)
		destination = p->pos.y + p->dir.y * move;
	else
		destination = p->pos.y + p->dir.x * move;
	if (destination - p->pos.y > 0
			&& map[(int)p->pos.y + 1][(int)p->pos.x] != '0'
			&& destination - (int)p->pos.y > 0.95)
		p->pos.y = (int)p->pos.y + 0.95;
	else if (destination - p->pos.y < 0
			&& map[(int)p->pos.y - 1][(int)p->pos.x] != '0'
			&& (int)p->pos.y + 1 - destination > 0.95)
		p->pos.y = (int)p->pos.y + 0.05;
	else
		p->pos.y = destination;
}

static void	move_x_player(t_player *p, char **map, int key)
{
	double	move;
	double	destination;

	move = MOVE;
	if (key == S_KEY || key == A_KEY)
		move *= -1;
	if (key == W_KEY || key == S_KEY)
		destination = p->pos.x + p->dir.x * move;
	else
		destination = p->pos.x - p->dir.y * move;
	if (destination - p->pos.x > 0
			&& map[(int)p->pos.y][(int)p->pos.x + 1] != '0'
			&& destination - (int)p->pos.x > 0.95)
		p->pos.x = (int)p->pos.x + 0.95;
	else if (destination - p->pos.x < 0
			&& map[(int)p->pos.y][(int)p->pos.x - 1] != '0'
			&& (int)p->pos.x + 1 - destination > 0.95)
		p->pos.x = (int)p->pos.x + 0.05;
	else
		p->pos.x = destination;
}

static void	rotate_player(t_player *p, int key)
{
	double	radian;
	double	tmp;

	radian = RADIAN;
	if (key == LEFT_KEY)
		radian *= -1;
	tmp = p->dir.x;
	p->dir.x = p->dir.x * cos(radian) - p->dir.y * sin(radian);
	p->dir.y = tmp * sin(radian) + p->dir.y * cos(radian);
	tmp = p->plane.x;
	p->plane.x = p->plane.x * cos(radian) - p->plane.y * sin(radian);
	p->plane.y = tmp * sin(radian) + p->plane.y * cos(radian);
}

int			deal_key(int key, t_data *d)
{
	if (key == ESC_KEY)
		finish_program(d, SUCCESS);
	else if (key == W_KEY || key == A_KEY || key == S_KEY || key == D_KEY)
	{
		move_y_player(&d->player, d->stage.map, key);
		move_x_player(&d->player, d->stage.map, key);
		draw_to_img(d);
		mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	}
	else if (key == LEFT_KEY || key == RIGHT_KEY)
	{
		rotate_player(&d->player, key);
		draw_to_img(d);
		mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	}
	return (1);
}
