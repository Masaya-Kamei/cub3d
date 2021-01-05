/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   others.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/05 18:03:49 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/05 19:03:50 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

#if __linux__

void	destroy_display(t_data *d)
{
	mlx_destroy_display(d->mlx);
	free(d->mlx);
}

#else

void	destroy_display(t_data *d)
{
	d = (t_data *)d;
}

#endif

int		finish_program_by_destory(t_data *d)
{
	finish_program(d, SUCCESS);
	return (1);
}

int		put_image_to_window_by_focusin(t_data *d)
{
	mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	return (1);
}
