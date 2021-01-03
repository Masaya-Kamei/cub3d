/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:35:25 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/03 15:59:19 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static t_ray	get_ray(t_player p, int draw_x, int win_width)
{
	t_ray	ray;
	double	camera_x;

	camera_x = -1 + (2.0 / win_width) * draw_x;
	ray.x = p.dir.x + p.plane.x * camera_x;
	ray.y = p.dir.y + p.plane.y * camera_x;
	ray.delta_dist.x = sqrt(1 + pow(ray.y / ray.x, 2));
	ray.delta_dist.y = sqrt(1 + pow(ray.x / ray.y, 2));
	if (ray.x < 0)
		ray.side_dist.x = (p.pos.x - floor(p.pos.x)) * ray.delta_dist.x;
	else
		ray.side_dist.x = (floor(p.pos.x + 1) - p.pos.x) * ray.delta_dist.x;
	if (ray.y < 0)
		ray.side_dist.y = (p.pos.y - floor(p.pos.y)) * ray.delta_dist.y;
	else
		ray.side_dist.y = (floor(p.pos.y + 1) - p.pos.y) * ray.delta_dist.y;
	ray.tip.x = floor(p.pos.x);
	ray.tip.y = floor(p.pos.y);
	ray.sprite_lst = NULL;
	return (ray);
}

static double	get_dist_to_wall(t_data *d, t_ray *ray, char **map)
{
	while (map[(int)ray->tip.y][(int)ray->tip.x] != '1')
	{
		if (ray->side_dist.x < ray->side_dist.y)
		{
			ray->side_dist.x += ray->delta_dist.x;
			ray->tip.x += (ray->x < 0) ? -1 : 1;
			ray->hit_side = (ray->x < 0) ? EAST : WEST;
		}
		else
		{
			ray->side_dist.y += ray->delta_dist.y;
			ray->tip.y += (ray->y < 0) ? -1 : 1;
			ray->hit_side = (ray->y < 0) ? SOUTH : NOUTH;
		}
		if (map[(int)ray->tip.y][(int)ray->tip.x] == '2')
			add_sprite_to_list(d, ray, d->player);
	}
	if (ray->hit_side == WEST || ray->hit_side == EAST)
		ray->dist_to_wall = (ray->side_dist.x - ray->delta_dist.x)
													/ hypot(ray->x, ray->y);
	else
		ray->dist_to_wall = (ray->side_dist.y - ray->delta_dist.y)
													/ hypot(ray->x, ray->y);
	return (ray->dist_to_wall);
}

static void		set_info_of_draw_wall(t_data *d, t_ray ray,
													t_tex tex, int info[6])
{
	double ratio_x;

	info[WIN_HALF_HEIGHT] = d->win.height / 2;
	info[TEX_HEIGHT] = (int)((double)d->win.height / ray.dist_to_wall);
	info[TEX_START] = info[WIN_HALF_HEIGHT] - info[TEX_HEIGHT] / 2;
	info[TEX_END] = info[TEX_START] + info[TEX_HEIGHT];
	if (ray.hit_side == WEST || ray.hit_side == EAST)
		ratio_x = d->player.pos.y + ray.dist_to_wall * ray.y;
	else
		ratio_x = d->player.pos.x + ray.dist_to_wall * ray.x;
	if (ray.hit_side == SOUTH || ray.hit_side == WEST)
		ratio_x = ratio_x - floor(ratio_x);
	else
		ratio_x = ceil(ratio_x) - ratio_x;
	info[TEX_X] = (int)(ratio_x * (double)tex.width);
	if (tex.img.endian == 1)
		info[TEX_X] = tex.width - info[TEX_X] - 1;
}

static void		draw_wall_one_line(t_data *d, int draw_x, t_ray ray, t_tex tex)
{
	int				info[6];
	double			ratio_y;
	unsigned int	color;
	char			*dst;
	int				draw_y;

	set_info_of_draw_wall(d, ray, tex, info);
	draw_y = -1;
	while (++draw_y < d->win.height)
	{
		if (info[TEX_START] <= draw_y && draw_y < info[TEX_END])
		{
			ratio_y = (double)(draw_y - info[TEX_START]) / info[TEX_HEIGHT];
			info[TEX_Y] = (int)(ratio_y * (double)tex.height);
			color = *(unsigned int *)(tex.img.addr + info[TEX_Y]
			* tex.img.line_length + info[TEX_X] * (tex.img.bits_per_pixel / 8));
		}
		else if (draw_y < info[WIN_HALF_HEIGHT])
			color = d->stage.color[CEIL];
		else
			color = d->stage.color[FLOOR];
		dst = d->img.addr + draw_y * d->img.line_length
										+ draw_x * (d->img.bits_per_pixel / 8);
		*(unsigned int *)dst = color;
	}
}

void			draw_to_img(t_data *d)
{
	t_ray		ray;
	int			draw_x;
	t_sprite	sprite;
	t_list		*next;

	draw_x = 0;
	while (draw_x < d->win.width)
	{
		if (d->img.endian == 1)
			draw_x = d->win.width - draw_x - 1;
		ray = get_ray(d->player, draw_x, d->win.width);
		ray.dist_to_wall = get_dist_to_wall(d, &ray, d->stage.map);
		draw_wall_one_line(d, draw_x, ray, d->tex[ray.hit_side]);
		while (ray.sprite_lst != NULL)
		{
			sprite = *(t_sprite *)ray.sprite_lst->content;
			draw_sprite_one_line(d, draw_x, sprite, d->tex[SPRITE]);
			next = ray.sprite_lst->next;
			free(ray.sprite_lst->content);
			free(ray.sprite_lst);
			ray.sprite_lst = next;
		}
		draw_x += 1;
	}
}
