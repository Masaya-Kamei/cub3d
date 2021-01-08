/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_sprite.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/12 11:06:52 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/07 16:27:55 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static double	get_dist_to_sprite(t_ray ray, t_player p)
{
	t_vector	vec;
	double		theta;
	double		dist_to_sprite;

	theta = atan(p.dir.x / p.dir.y);
	vec.x = ray.tip.x + 0.5 - p.pos.x;
	vec.y = ray.tip.y + 0.5 - p.pos.y;
	if (acos((vec.x * p.dir.x + vec.y * p.dir.y) / hypot(vec.x, vec.y))
																>= PI / 2)
		dist_to_sprite = OUT_OF_RANGE;
	else
	{
		dist_to_sprite = vec.x * sin(theta) + vec.y * cos(theta);
		dist_to_sprite = fabs(dist_to_sprite);
	}
	return (dist_to_sprite);
}

static double	get_ratio_x_of_sprite(t_ray ray, t_player p)
{
	t_vector	vec;
	double		theta_l;
	double		theta_r;
	double		theta;
	double		ratio_x;

	vec.x = ray.tip.x + 0.5 - p.pos.x + p.dir.y * 0.5;
	vec.y = ray.tip.y + 0.5 - p.pos.y - p.dir.x * 0.5;
	theta_r = acos((vec.x * p.dir.y + vec.y * -p.dir.x) / hypot(vec.x, vec.y));
	vec.x = ray.tip.x + 0.5 - p.pos.x - p.dir.y * 0.5;
	vec.y = ray.tip.y + 0.5 - p.pos.y + p.dir.x * 0.5;
	theta_l = acos((vec.x * p.dir.y + vec.y * -p.dir.x) / hypot(vec.x, vec.y));
	theta = acos((ray.x * p.dir.y + ray.y * -p.dir.x) / hypot(ray.x, ray.y));
	if (theta_r <= theta && theta <= theta_l)
		ratio_x = (theta_l - theta) / (theta_l - theta_r);
	else
		ratio_x = OUT_OF_RANGE;
	return (ratio_x);
}

void			add_sprite_to_list(t_data *d, t_ray *ray, t_player p)
{
	t_sprite	*sp;
	t_list		*new;

	if (!(sp = (t_sprite *)malloc(sizeof(t_sprite))))
	{
		ft_lstclear(&ray->sprite_lst, free);
		finish_program(d, MALLOC_ERROR);
	}
	sp->dist_to_sprite = get_dist_to_sprite(*ray, p);
	sp->ratio_x = get_ratio_x_of_sprite(*ray, p);
	if (sp->dist_to_sprite == OUT_OF_RANGE || sp->ratio_x == OUT_OF_RANGE)
		free(sp);
	else
	{
		if (!(new = ft_lstnew(sp)))
		{
			free(sp);
			ft_lstclear(&ray->sprite_lst, free);
			finish_program(d, MALLOC_ERROR);
		}
		ft_lstadd_front(&ray->sprite_lst, new);
	}
}

static void		set_info_of_draw_sprite(t_data *d, t_sprite sp,
													t_tex tex, int info[6])
{
	double ratio_x;

	info[WIN_HALF_HEIGHT] = d->win.height / 2;
	info[TEX_HEIGHT] = (int)((double)d->win.height / sp.dist_to_sprite);
	info[TEX_START] = info[WIN_HALF_HEIGHT] - info[TEX_HEIGHT] / 2;
	info[TEX_END] = info[TEX_START] + info[TEX_HEIGHT];
	ratio_x = sp.ratio_x;
	info[TEX_X] = (int)(ratio_x * (double)tex.width);
	if (tex.img.endian == 1)
		info[TEX_X] = tex.width - info[TEX_X] - 1;
}

void			draw_sprite_one_line(t_data *d, int draw_x,
													t_sprite sp, t_tex tex)
{
	int				info[6];
	double			ratio_y;
	unsigned int	color;
	char			*dst;
	int				draw_y;

	set_info_of_draw_sprite(d, sp, tex, info);
	draw_y = 0;
	while (draw_y < d->win.height)
	{
		if (info[TEX_START] <= draw_y && draw_y < info[TEX_END])
		{
			ratio_y = (double)(draw_y - info[TEX_START]) / info[TEX_HEIGHT];
			info[TEX_Y] = (int)(ratio_y * (double)tex.height);
			color = *(unsigned int *)(tex.img.addr + info[TEX_Y]
			* tex.img.line_length + info[TEX_X] * (tex.img.bits_per_pixel / 8));
			dst = d->img.addr + draw_y * d->img.line_length +
										draw_x * (d->img.bits_per_pixel / 8);
			if (color != 0)
				*(unsigned int *)dst = color;
		}
		draw_y++;
	}
}
