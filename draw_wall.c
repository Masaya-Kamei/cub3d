/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:35:25 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/05 21:48:21 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_ray get_ray(t_player player, int drawX, int winWidth)
{
	t_ray ray;
	double cameraX;

	cameraX = -1 + (2.0 / winWidth) * drawX;
	// printf("	%d, %d, %lf", drawX, winWidth, cameraX);
	ray.x = player.dir.x + player.plane.x * cameraX;
	ray.y = player.dir.y + player.plane.y * cameraX;
	ray.deltaDist.x = sqrt(1 + pow(ray.y / ray.x, 2));
	ray.deltaDist.y = sqrt(1 + pow(ray.x / ray.y, 2));
	if (ray.x < 0)
		ray.sideDist.x = (player.pos.x - floor(player.pos.x)) * ray.deltaDist.x;
	else
		ray.sideDist.x = (ceil(player.pos.x) - player.pos.x) * ray.deltaDist.x;
	if (ray.y < 0)
		ray.sideDist.y = (player.pos.y - floor(player.pos.y)) * ray.deltaDist.y;
	else
		ray.sideDist.y = (ceil(player.pos.y) - player.pos.y) * ray.deltaDist.x;
	printf(" ~%lf, %lf, %lf, %lf~ ", ray.sideDist.x, ray.sideDist.y, ray.deltaDist.x, ray.deltaDist.y);
	ray.tip.x = floor(player.pos.x);
	ray.tip.y = floor(player.pos.y);

	return (ray);
}

double get_distanceToWall(t_ray ray, char **map)
{
	int stepX;
	int stepY;
	int side;
	double distanceToWall;

	stepX = (ray.x < 0) ? -1 : 1;
	stepY = (ray.y < 0) ? -1 : 1;
	while (map[(int)ray.tip.y][(int)ray.tip.x] != '1')
	{
		if(ray.sideDist.x < ray.sideDist.y)
		{
			// if (ray.tip.x != floor(player.pos.x))
			ray.sideDist.x += ray.deltaDist.x;
			ray.tip.x += stepX;
			printf(" [x %.0lf, %.0lf, %3.3lf, =%c]", ray.tip.x, ray.tip.y, ray.sideDist.x, map[(int)ray.tip.y][(int)ray.tip.x]);
			side = 1;
		}
		else
		{
			// if (ray.tip.y != floor(player.pos.y))
			ray.sideDist.y += ray.deltaDist.y;
			ray.tip.y += stepY;
			printf(" [y %.0lf, %.0lf, %3.3lf, =%c]", ray.tip.x, ray.tip.y, ray.sideDist.y, map[(int)ray.tip.y][(int)ray.tip.x]);
			side = 0;
		}
		// printf(" =%c=", map[(int)ray.tip.y][(int)ray.tip.x]);
	}
	if (side == 1)
	{
		distanceToWall = (ray.sideDist.x - ray.deltaDist.x) / hypot(ray.x, ray.y);
		printf(" %d, %lf", side, distanceToWall);
		// printf("	%d, %lf, %lf, %lf", side, distanceToWall, ray.x, ray.y);
	}
	else
	{
		distanceToWall = (ray.sideDist.y - ray.deltaDist.y) / hypot(ray.x, ray.y);
		printf(" %d, %lf", side, distanceToWall);
		// printf("	%d, %lf, %lf, %lf", side, distanceToWall, ray.x, ray.y);
	}
	// if (side == 1)
	// {
	// 	distanceToWall = (ray.tip.x - player.pos.x + (1 - stepX) / 2) / ray.x;
	// 	printf(" %d, %lf", side, distanceToWall);
	// 	// printf("	%lf, %lf, %lf", distanceToWall, ray.x, ray.y);
	// }
	// else
	// {
	// 	distanceToWall = (ray.tip.y - player.pos.y + (1 - stepY) / 2) / ray.y;
	// 	printf(" %d, %lf", side, distanceToWall);
	// 	// printf("	%lf, %lf, %lf", distanceToWall, ray.x, ray.y);
	// }
	return (distanceToWall);
}

void	draw_one_column(t_data *d, double distanceToWall, int drawX)
{
	int drawHeight;
	int drawY;
	int drawEnd;

	drawHeight = (int)((double)d->win.height / distanceToWall);
	// printf("	%d = %d / %lf", drawHeight, d->win.height, distanceToWall);
	drawY = d->win.height / 2 - drawHeight / 2;
	drawEnd = d->win.height / 2 + drawHeight / 2;
	while (drawY < drawEnd)
	{
		mlx_pixel_put(d->mlx, d->win.win, drawX, drawY, 0x00AA0000);
		drawY += 1;
	}
}

int draw_wall(t_data *d)
{
	t_ray ray;
	double distanceToWall;
	int		drawX;

	for (int i = 0; i < 10; i++)
		printf("%s\n", d->stage.map[i]);
	drawX = 0;
	while (drawX < d->win.width)
	{
		printf("%3d", drawX);
		ray = get_ray(d->player, drawX, d->win.width);
		printf(" ray");
		distanceToWall = get_distanceToWall(ray, d->stage.map);
		printf(" dis");
		draw_one_column(d, distanceToWall, drawX);
		printf(" draw\n");
		drawX += 1;
	}
	return (0);
}
