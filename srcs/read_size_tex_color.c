/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_size_tex_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:53:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/03 17:32:41 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_window_size(t_data *d, char *width, char *height)
{
	int i;
	int	max_width;
	int	max_height;

	if (d->win.width != NOT_READ)
		return (R_DOUBLE_READ);
	i = 0;
	while (width[i] != '\0')
		if (ft_isdigit(width[i++]) == 0)
			return (R_NOT_NUMBER);
	i = 0;
	while (height[i] != '\0')
		if (ft_isdigit(height[i++]) == 0)
			return (R_NOT_NUMBER);
	d->win.width = ft_atoi(width);
	d->win.height = ft_atoi(height);
	mlx_get_screen_size(d->mlx, &max_width, &max_height);
	if (d->win.width <= 0 || d->win.height <= 0
			|| d->win.width > max_width || d->win.height > max_height)
		return (R_OUT_OF_RANGE);
	return (SUCCESS);
}

static int	read_texture(t_data *d, char *tex_path, int side)
{
	if (d->tex[side].img.img != NULL)
		return (TEX_DOUBLE_READ);
	if (ft_strlen(tex_path) <= 4 ||
		(ft_strncmp(tex_path + ft_strlen(tex_path) - 4, ".xpm", 5) != 0
			&& ft_strncmp(tex_path + ft_strlen(tex_path) - 4, ".png", 5) != 0))
		return (TEX_INVALID_EX);
	d->tex[side].img.img = mlx_xpm_file_to_image(d->mlx, tex_path,
								&d->tex[side].width, &d->tex[side].height);
	if (d->tex[side].img.img == NULL)
	{
		write(2, "Error\n", 7);
		perror(tex_path);
		return (FILE_OPEN_ERROR);
	}
	d->tex[side].img.addr = mlx_get_data_addr(d->tex[side].img.img,
		&d->tex[side].img.bits_per_pixel, &d->tex[side].img.line_length,
												&d->tex[side].img.endian);
	return (SUCCESS);
}

static int	get_rgb_nbr(char **rgb_str, int rgb_nbr[3])
{
	int		i;
	int		j;

	i = 0;
	while (i < 3)
	{
		j = 0;
		while (rgb_str[i][j] != '\0')
		{
			if (ft_isdigit(rgb_str[i][j]) == 0)
				return (COLOR_NOT_NUMBER);
			j++;
		}
		rgb_nbr[i] = ft_atoi(rgb_str[i]);
		if (rgb_nbr[i] < 0 || rgb_nbr[i] > 255)
			return (COLOR_OUT_OF_RANGE);
		i++;
	}
	return (SUCCESS);
}

static int	read_color(t_data *d, char *color, int place)
{
	char	**rgb_str;
	int		rgb_nbr[3];
	int		ret;

	if (d->stage.color[place] != NOT_READ)
		return (COLOR_DOUBLE_READ);
	if (!(rgb_str = ft_split(color, ',')))
		return (MALLOC_ERROR);
	if (!rgb_str[0] || !rgb_str[1] || !rgb_str[2] || rgb_str[3])
	{
		free_double_pointer(rgb_str);
		return (COLOR_NOT_TWO_COMMAS);
	}
	ret = get_rgb_nbr(rgb_str, rgb_nbr);
	free_double_pointer(rgb_str);
	if (ret != SUCCESS)
		return (ret);
	d->stage.color[place] = 256 * 256 * rgb_nbr[0] + 256 * rgb_nbr[1]
															+ rgb_nbr[2];
	return (SUCCESS);
}

int			branch_size_tex_color(t_data *d, char **str)
{
	int flag;

	if (str[0] == NULL)
		flag = SUCCESS;
	else if (ft_strncmp(str[0], "R", 2) == 0 && str[1] && str[2] && !str[3])
		flag = read_window_size(d, str[1], str[2]);
	else if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d, str[1], NOUTH);
	else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d, str[1], SOUTH);
	else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d, str[1], WEST);
	else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d, str[1], EAST);
	else if (ft_strncmp(str[0], "S", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d, str[1], SPRITE);
	else if (ft_strncmp(str[0], "F", 2) == 0 && str[1] && !str[2])
		flag = read_color(d, str[1], FLOOR);
	else if (ft_strncmp(str[0], "C", 2) == 0 && str[1] && !str[2])
		flag = read_color(d, str[1], CEIL);
	else
		flag = NOT_ENOUGH_ELEMENT_OR_INVALID_SETTING;
	return (flag);
}
