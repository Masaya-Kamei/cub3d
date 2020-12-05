/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:58 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/05 21:53:34 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_cub(t_data *d)
{
	d->win.width = 800;
	d->win.height = 640;
	d->stage.c_color = 0x000000EE;
	d->stage.f_color = 0x00AAAAAA;
	d->stage.n_texture = ft_strdup("./textures/north.xpm");
	d->stage.s_texture = ft_strdup("./textures/south.xpm");
	d->stage.e_texture = ft_strdup("./textures/east.xpm");
	d->stage.w_texture = ft_strdup("./textures/west.xpm");

	d->stage.map = (char **)malloc(sizeof(char *) * 10);
	d->stage.map[0] = ft_strdup("11111111111111111101");
	d->stage.map[1] = ft_strdup("10000000001000010001");
	d->stage.map[2] = ft_strdup("10000000001000010001");
	d->stage.map[3] = ft_strdup("10000000001000011111");
	d->stage.map[4] = ft_strdup("10000000001000000001");
	d->stage.map[5] = ft_strdup("10000000001000N00001");
	d->stage.map[6] = ft_strdup("10000000001000000001");
	d->stage.map[7] = ft_strdup("10000000000000000001");
	d->stage.map[8] = ft_strdup("1000000000000000001");
	d->stage.map[9] = ft_strdup("11111111111111111111");

	d->player.pos.x = 14.5;
	d->player.pos.y = 5.5;
	d->player.dir.x = 0;
	d->player.dir.y = -1;
	d->player.plane.x = 0.66;
	d->player.plane.y = 0;

	return (1);
}
