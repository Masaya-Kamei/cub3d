/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:30:35 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/05 13:01:27 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		deal_key(int key, t_data *d)
{
	if (key == 53)
	{
		mlx_destroy_window(d->mlx, d->win.win);
		exit(0);
	}
	return (1);
}

int		draw_floor_and_ceiling(t_data d)
{
	int i;
	int j;
	int color;

	i= 0;
	while (i < d.win.width)
	{
			color = d.stage.c_color;
			j = 0;
			while (j < d.win.height)
			{
					mlx_pixel_put(d.mlx, d.win.win, i, j, color);
					if (j == d.win.height / 2)
						color = d.stage.f_color;
					j++;
			}
			i++;
	}
	return (1);
}

int		main(void)
{
	t_data d;

	if (read_cub(&d) == 0)
		return (0);
	d.mlx = mlx_init();
	d.win.win = mlx_new_window(d.mlx, d.win.width, d.win.height, "FPS");
	draw_floor_and_ceiling(d);
	draw_wall(&d);
	mlx_key_hook(d.win.win, deal_key, &d);
	mlx_loop(d.mlx);
	return (0);
}
