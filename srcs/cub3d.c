/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:30:35 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/02 14:48:53 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void		free_double_pointer(char **str)
{
	int i;

	i = 0;
	while (str[i] != NULL)
		free(str[i++]);
	free(str);
}

void		finish_program(t_data *d, int error_nbr)
{
	if (error_nbr != SUCCESS && error_nbr != FILE_OPEN_ERROR)
	{
		write(2, "Error\n", 7);
		write(2, d->error_msg[error_nbr], ft_strlen(d->error_msg[error_nbr]));
	}
	if (d->stage.map != NULL)
		free_double_pointer(d->stage.map);
	if (d->tex[NOUTH].img.img != NULL)
		mlx_destroy_image(d->mlx, d->tex[NOUTH].img.img);
	if (d->tex[SOUTH].img.img != NULL)
		mlx_destroy_image(d->mlx, d->tex[SOUTH].img.img);
	if (d->tex[EAST].img.img != NULL)
		mlx_destroy_image(d->mlx, d->tex[EAST].img.img);
	if (d->tex[WEST].img.img != NULL)
		mlx_destroy_image(d->mlx, d->tex[WEST].img.img);
	if (d->tex[SPRITE].img.img != NULL)
		mlx_destroy_image(d->mlx, d->tex[SPRITE].img.img);
	if (d->img.img != NULL)
		mlx_destroy_image(d->mlx, d->img.img);
	if (d->win.win != NULL)
		mlx_destroy_window(d->mlx, d->win.win);
	exit(0);
	// printf("end\n");
	// while (1){};
}

static void	set_error_msg(char e[30][50])
{
	ft_strlcpy(e[MALLOC_ERROR], "Malloc error\n", 14);
	ft_strlcpy(e[NOT_ENOUGH_ELEMENT], "Not enough element\n", 20);
	ft_strlcpy(e[GNL_ERROR], "Get_next_line error\n", 11);
	ft_strlcpy(e[R_DOUBLE_READ], "R element was read in double\n", 23);
	ft_strlcpy(e[R_NOT_NUMBER], "R element is not number\n", 22);
	ft_strlcpy(e[R_OUT_OF_RANGE], "R element is out of range", 23);
	ft_strlcpy(e[NOT_ENOUGH_ELEMENT_OR_INVALID_SETTING],
								"Not enough elements or Invalid setting\n", 40);
	ft_strlcpy(e[TEX_DOUBLE_READ], "Texture element was read in double\n", 36);
	ft_strlcpy(e[TEX_INVALID_EXTENSION],
								"Texture element is invalid extension\n", 38);
	ft_strlcpy(e[COLOR_DOUBLE_READ], "Color element was read in double\n", 27);
	ft_strlcpy(e[COLOR_NOT_TWO_COMMAS],
								"Color element doesn't have two commas\n", 30);
	ft_strlcpy(e[COLOR_NOT_NUMBER], "Color element is not number\n", 26);
	ft_strlcpy(e[COLOR_OUT_OF_RANGE], "Color element is out of range\n", 28);
	ft_strlcpy(e[NOT_END_MAP], "There are characters under the map\n", 36);
	ft_strlcpy(e[SMALL_MAP], "SMALL_MAP\n", 11);
	ft_strlcpy(e[PLAYER_DOUBLE], "PLAYER_DOUBLE\n", 15);
	ft_strlcpy(e[INVALID_CHARACTER_IN_MAP], "INVALID_CHARACTER_IN_MAP\n", 26);
	ft_strlcpy(e[NOT_DETECTED_PLAYER], "NOT_DETECTED_PLAYER\n", 21);
	ft_strlcpy(e[DETECTED_SPACE_IN_ROOM], "DETECTED_SPACE_IN_ROOM\n", 24);
	ft_strlcpy(e[NOT_ARROUND_WALL], "NOT_ARROUND_WALL\n", 18);
	ft_strlcpy(e[COMMAND_LINE_ERROR], "Command line arguments error\n", 30);
	ft_strlcpy(e[NOT_CUB_FILE], "First command line argument isn't .cub\n", 40);
}

static void	initialize_data(t_data *d)
{
	d->stage.map = NULL;
	d->img.img = NULL;
	d->win.win = NULL;
	d->tex[NOUTH].img.img = NULL;
	d->tex[SOUTH].img.img = NULL;
	d->tex[EAST].img.img = NULL;
	d->tex[WEST].img.img = NULL;
	d->tex[SPRITE].img.img = NULL;
	set_error_msg(d->error_msg);
}

int			main(int argc, char *argv[])
{
	t_data d;

	initialize_data(&d);
	if (argc <= 1 || argc >= 4 ||
			(argc == 3 && ft_strncmp(argv[2], "--save", 7) != 0))
		finish_program(&d, COMMAND_LINE_ERROR);
	else if (ft_strlen(argv[1]) <= 4 ||
				ft_strncmp(argv[1] + ft_strlen(argv[1]) - 4, ".cub", 5) != 0)
		finish_program(&d, NOT_CUB_FILE);
	d.mlx = mlx_init();
	read_conf_file(&d, argv[1]);
	d.img.img = mlx_new_image(d.mlx, d.win.width, d.win.height);
	d.img.addr = mlx_get_data_addr(d.img.img, &d.img.bits_per_pixel,
										&d.img.line_length, &d.img.endian);
	d.img.width = d.win.width;
	d.img.height = d.win.height;
	draw_to_img(&d);
	if (argc == 3)
		save_bmp(&d, d.img);
	d.win.win = mlx_new_window(d.mlx, d.win.width, d.win.height, "FPS");
	mlx_put_image_to_window(d.mlx, d.win.win, d.img.img, 0, 0);
	mlx_hook(d.win.win, 2, 1L << 0, deal_key, &d);
	mlx_loop(d.mlx);
	return (0);
}
