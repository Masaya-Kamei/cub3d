/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:30:35 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/08 12:50:34 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// 0.2秒で１マス進む
// 1回で0.25マス進む
int		move_player(t_data *d, int key)
{
	double movePerLoop;
	double rotPerLoop;
	double oldDirX;
	double oldPlaneX;
	// 1回
	movePerLoop = 0.25;
	rotPerLoop = 0.2;
	if (key == UP || key == DOWN)
	{
		// printf("%lf, %lf, =%c", d->player.pos.x, d->player.pos.y, d->stage.map[(int)d->player.pos.y][(int)d->player.pos.x]);
		if (key == DOWN)
			movePerLoop *= -1;
		if (d->stage.map[(int)(d->player.pos.y + d->player.dir.y * movePerLoop)][(int)d->player.pos.x] != '1')
			d->player.pos.y += d->player.dir.y * movePerLoop;
		if (d->stage.map[(int)d->player.pos.y][(int)(d->player.pos.x + d->player.dir.x * movePerLoop)] != '1')
			d->player.pos.x += d->player.dir.x * movePerLoop;
		// printf("	%lf, %lf, =%c\n", d->player.pos.x, d->player.pos.y, d->stage.map[(int)d->player.pos.y][(int)d->player.pos.x]);
	}
	else if (key == RIGHT || key == LEFT)
	{
		if (key == LEFT)
			rotPerLoop *= -1;
		oldDirX = d->player.dir.x;
		d->player.dir.x = d->player.dir.x * cos(rotPerLoop) - d->player.dir.y * sin(rotPerLoop);
		d->player.dir.y = oldDirX * sin(rotPerLoop) + d->player.dir.y * cos(rotPerLoop);
		oldPlaneX = d->player.plane.x;
		d->player.plane.x = d->player.plane.x * cos(rotPerLoop) - d->player.plane.y * sin(rotPerLoop);
		d->player.plane.y = oldPlaneX * sin(rotPerLoop) + d->player.plane.y * cos(rotPerLoop);
	}
	return (0);
}


int		deal_key(int key, t_data *d)
{
	if (key == ESC)
	{
		mlx_destroy_window(d->mlx, d->win.win);
		exit(0);
	}
	else if (key == UP || key == DOWN || key == RIGHT || key == LEFT)
	{
		move_player(d, key);
		draw_to_win(d);
		// mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);/
	}
	// 0.08秒/1回
	// struct timeval myTime;
    // gettimeofday(&myTime, NULL);
    // printf("%04ld.%06d\n", myTime.tv_sec, myTime.tv_usec);

	return (1);
}


int		main(void)
{
	t_data d;

	d.mlx = mlx_init();
	if (read_cub(&d) == 0)
		return (0);
	d.win.win = mlx_new_window(d.mlx, d.win.width, d.win.height, "FPS");
	// draw_floor_and_ceiling(d);
	d.img.img = mlx_new_image(d.mlx, d.win.width, d.win.height);
    d.img.addr = mlx_get_data_addr(d.img.img, &d.img.bits_per_pixel, &d.img.line_length, &d.img.endian);
	draw_to_win(&d);
	// mlx_put_image_to_window(d.mlx, d.win.win, d.img.img, 0, 0);

	// mlx_key_hook(d.win.win, deal_key, &d);
	mlx_hook(d.win.win, 2, 1L<<0, deal_key, &d);
	mlx_loop(d.mlx);
	return (0);
}

// int		draw_floor_and_ceiling(t_data d)
// {
// 	int i;
// 	int j;
// 	int color;

// 	i= 0;
// 	while (i < d.win.width)
// 	{
// 			color = d.stage.c_color;
// 			j = 0;
// 			while (j < d.win.height)
// 			{
// 					mlx_pixel_put(d.mlx, d.win.win, i, j, color);
// 					if (j == d.win.height / 2)
// 						color = d.stage.f_color;
// 					j++;
// 			}
// 			i++;
// 	}
// 	return (1);
// }
