/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_cub.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:16:58 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/08 12:54:04 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		read_cub(t_data *d)
{
	d->win.width = 800;
	d->win.height = 640;
	d->stage.c_color = 0x000000EE;
	d->stage.f_color = 0x00DDDDDD;

	// d->stage.n_tex.path = ft_strdup("./textures/north.xpm");
	// d->stage.s_tex.path = ft_strdup("./textures/south.xpm");
	// d->stage.e_tex.path = ft_strdup("./textures/east.xpm");
	// d->stage.w_tex.path = ft_strdup("./textures/west.xpm");

	d->stage.n_tex.img.img = mlx_xpm_file_to_image(d->mlx, "./textures/north.xpm", &d->stage.n_tex.width, &d->stage.n_tex.height);
	d->stage.n_tex.img.addr = mlx_get_data_addr(d->stage.n_tex.img.img, &d->stage.n_tex.img.bits_per_pixel, &d->stage.n_tex.img.line_length, &d->stage.n_tex.img.endian);

	d->stage.s_tex.img.img = mlx_xpm_file_to_image(d->mlx, "./textures/south.xpm", &d->stage.s_tex.width, &d->stage.s_tex.height);
	d->stage.s_tex.img.addr = mlx_get_data_addr(d->stage.s_tex.img.img, &d->stage.s_tex.img.bits_per_pixel, &d->stage.s_tex.img.line_length, &d->stage.s_tex.img.endian);

	d->stage.e_tex.img.img = mlx_xpm_file_to_image(d->mlx, "./textures/east.xpm", &d->stage.e_tex.width, &d->stage.e_tex.height);
	d->stage.e_tex.img.addr = mlx_get_data_addr(d->stage.e_tex.img.img, &d->stage.e_tex.img.bits_per_pixel, &d->stage.e_tex.img.line_length, &d->stage.e_tex.img.endian);

	d->stage.w_tex.img.img = mlx_xpm_file_to_image(d->mlx, "./textures/west.xpm", &d->stage.w_tex.width, &d->stage.w_tex.height);
	d->stage.w_tex.img.addr = mlx_get_data_addr(d->stage.w_tex.img.img, &d->stage.w_tex.img.bits_per_pixel, &d->stage.w_tex.img.line_length, &d->stage.w_tex.img.endian);

	d->stage.map = (char **)malloc(sizeof(char *) * 10);
	//							 01234567890123456789
	d->stage.map[0] = ft_strdup("11111111111111111101");
	d->stage.map[1] = ft_strdup("10000000001000010001");
	d->stage.map[2] = ft_strdup("10000000001000010001");
	d->stage.map[3] = ft_strdup("10000000001000011111");
	d->stage.map[4] = ft_strdup("10000000001000000001");
	d->stage.map[5] = ft_strdup("10000000001000000001");
	d->stage.map[6] = ft_strdup("10000000001000000001");
	d->stage.map[7] = ft_strdup("10000000000000000001");
	d->stage.map[8] = ft_strdup("10000000000000000001");
	d->stage.map[9] = ft_strdup("11111111111111111111");

	d->player.pos.x = 14.5;
	d->player.pos.y = 5.5;
	d->player.dir.x = 0;
	d->player.dir.y = 1;
	d->player.plane.x = -0.66;
	d->player.plane.y = 0;

	return (1);
}
