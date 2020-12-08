/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_wall.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/05 11:35:25 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/08 16:43:07 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"


t_ray get_ray(t_player player, int drawX, int winWidth)
{
	t_ray ray;
	double cameraX;

	cameraX = -1 + (2.0 / winWidth) * drawX;
	ray.x = player.dir.x + player.plane.x * cameraX;
	ray.y = player.dir.y + player.plane.y * cameraX;
	printf("	%1.5lf, %1.5lf, plane.x:%lf, cameraX:%lf, dir.x:%lf, dir.y:%lf", ray.x, ray.y, player.plane.x, cameraX, player.dir.x, player.dir.y);
	if (ray.x == 0)
		ray.x = 0.0000000001;
	if (ray.y == 0)
		ray.y = 0.0000000001;
	// printf("	%1.20lf, %1.20lf\n", ray.x, ray.y);
	ray.deltaDist.x = sqrt(1 + pow(ray.y / ray.x, 2));
	ray.deltaDist.y = sqrt(1 + pow(ray.x / ray.y, 2));
	if (ray.x < 0)
		ray.sideDist.x = (player.pos.x - floor(player.pos.x)) * ray.deltaDist.x;
	else
		ray.sideDist.x = (ceil(player.pos.x) - player.pos.x) * ray.deltaDist.x;
	if (ray.y < 0)
		ray.sideDist.y = (player.pos.y - floor(player.pos.y)) * ray.deltaDist.y;
	else
		ray.sideDist.y = (ceil(player.pos.y) - player.pos.y) * ray.deltaDist.y;
	// printf(" ~%lf, %lf, %lf, %lf~ ", ray.sideDist.x, ray.sideDist.y, ray.deltaDist.x, ray.deltaDist.y);
	ray.tip.x = floor(player.pos.x);
	ray.tip.y = floor(player.pos.y);

	return (ray);
}

double get_distanceToWall(t_ray *ray, char **map)
{
	int stepX;
	int stepY;
	// int side;
	double distanceToWall;

	stepX = (ray->x < 0) ? -1 : 1;
	stepY = (ray->y < 0) ? -1 : 1;
	while (map[(int)ray->tip.y][(int)ray->tip.x] != '1')
	{
		if(ray->sideDist.x < ray->sideDist.y)
		{
			ray->sideDist.x += ray->deltaDist.x;
			ray->tip.x += stepX;
			// printf(" [x %.0lf, %.0lf, %3.3lf, =%c]", ray->tip.x, ray->tip.y, ray->sideDist.x, map[(int)ray->tip.y][(int)ray->tip.x]);
			ray->hitSide = (stepX == 1) ? RIGHT : LEFT;
		}
		else
		{
			ray->sideDist.y += ray->deltaDist.y;
			ray->tip.y += stepY;
			// printf(" [y %.0lf, %.0lf, %3.3lf, =%c]", ray->tip.x, ray->tip.y, ray->sideDist.y, map[(int)ray->tip.y][(int)ray->tip.x]);
			ray->hitSide = (stepY == 1) ? DOWN : UP;
		}
	}
	if (ray->hitSide == LEFT || ray->hitSide == RIGHT)
	{
		distanceToWall = (ray->sideDist.x - ray->deltaDist.x) / hypot(ray->x, ray->y);
		// printf(" %d, %lf", ray->hitSide, distanceToWall);
	}
	else
	{
		distanceToWall = (ray->sideDist.y - ray->deltaDist.y) / hypot(ray->x, ray->y);
		// printf(" %d, %lf", ray.hitSide, distanceToWall);
	}
	return (distanceToWall);
}
	// 	distanceToWall = (ray.tip.x - player.pos.x + (1 - stepX) / 2) / ray.x;
	// 	distanceToWall = (ray.tip.y - player.pos.y + (1 - stepY) / 2) / ray.y;

void	draw_one_column(t_data *d, double distanceToWall, int drawX, t_ray ray, t_texture tex)
{
	int drawWallHeight;
	int winHalfHeight;
	int drawY;
	int drawWallStart;
	int drawWallEnd;
	int color;
	char *dst;

	drawWallHeight = (int)((double)d->win.height / distanceToWall);
	winHalfHeight = d->win.height / 2;
	// printf("	%d = %d / %lf", drawWallHeight, d->win.height, distanceToWall);
	drawY = 0;
	drawWallStart = winHalfHeight - drawWallHeight / 2;
	drawWallEnd = winHalfHeight + drawWallHeight / 2;
	if (d->img.endian == 1)
		drawX = d->win.width - drawX - 1;

	double wallX;
	double wallY;
	if (ray.hitSide == LEFT || ray.hitSide == RIGHT)
		wallX = d->player.pos.y + distanceToWall * ray.y;
	else
		wallX = d->player.pos.x + distanceToWall * ray.x;
	if (ray.hitSide == UP || ray.hitSide == RIGHT)
		wallX = wallX - floor(wallX);
	else
		wallX = ceil(wallX) - wallX;

	// if (ray.hitSide == UP)
	// 	printf(" %lf", wallX);
	int texX = (int)(wallX * (double)tex.width);
	// if (ray.hitSide == LEFT)
	// 	texX = tex.width - texX - 1;
	// if (ray.hitSide == DOWN)
	// 	texX = tex.width - texX - 1;
	if (tex.img.endian == 1)
		texX = tex.width - texX - 1;

	//////////////////////////////////////////////////////////////////////


	// if (drawX >= 300 && drawX <= 500)
	// 	printf(" [%lf, %d]", wallX, texX);
	// printf("	%d, %d", drawWallHeight, drawWallStart);

	while (drawY < d->win.height)
	{
		if (drawWallStart <= drawY && drawY < drawWallEnd)
		{
			wallY = (double)(drawY - drawWallStart) / (double)drawWallHeight;
			int texY = (int)(wallY * (double)tex.height);

			// if (drawX == 400)
			// 	printf(" {%lf, %d}", wallY, texY);
			color = *(unsigned int *)(tex.img.addr + texY * tex.img.line_length + texX * (tex.img.bits_per_pixel / 8));

			// ray.hitSide = UP;
			// color = 0x00AA0000;
		}
		else if (drawY < winHalfHeight)
			color = d->stage.c_color;
		else
			color = d->stage.f_color;
		dst = d->img.addr + drawY * d->img.line_length + drawX * (d->img.bits_per_pixel / 8);
		*(unsigned int *)dst = color;
		// mlx_pixel_put(d->mlx, d->win.win, drawX, drawY, color);
		drawY += 1;
	}
}

int draw_to_win(t_data *d)
{
	t_ray ray;
	double distanceToWall;
	int		drawX;
	t_texture tex;

	// for (int i = 0; i < 10; i++)
	// 	printf("%s\n", d->stage.map[i]);
	drawX = 0;
	while (drawX < d->win.width)
	{
		printf("%3d", drawX);
		ray = get_ray(d->player, drawX, d->win.width);
		// printf(" ray");
		distanceToWall = get_distanceToWall(&ray, d->stage.map);
		// printf(" dis");
		if (ray.hitSide == UP)
			tex = d->stage.n_tex;
		else if (ray.hitSide == DOWN)
			tex = d->stage.s_tex;
		else if (ray.hitSide == LEFT)
			tex = d->stage.w_tex;
		else
			tex = d->stage.e_tex;

		draw_one_column(d, distanceToWall, drawX, ray, tex);
		printf(" draw\n");
		drawX += 1;
	}
    mlx_put_image_to_window(d->mlx, d->win.win, d->img.img, 0, 0);
	return (0);
}
