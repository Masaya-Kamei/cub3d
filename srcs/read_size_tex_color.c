/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_size_tex_color.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/12/31 18:53:53 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/10 13:28:14 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static int	read_window_size(void *mlx, t_win *win, char *width, char *height)
{
	int i;
	int	max_width;
	int	max_height;

	if (win->width != NOT_READ)
		return (R_DOUBLE_READ);
	i = 0;
	while (width[i] != '\0')
		if (ft_isdigit(width[i++]) == 0)
			return (R_NOT_NUMBER);
	if (i < 3 || i > 10 || (i == 10 && ft_strncmp(width, "2147483647", 11) > 0))
		return (R_OUT_OF_RANGE);
	i = 0;
	while (height[i] != '\0')
		if (ft_isdigit(height[i++]) == 0)
			return (R_NOT_NUMBER);
	if (i < 3 || i > 10 ||
					(i == 10 && ft_strncmp(height, "2147483647", 11) > 0))
		return (R_OUT_OF_RANGE);
	win->width = ft_atoi(width);
	win->height = ft_atoi(height);
	mlx_get_screen_size(mlx, &max_width, &max_height);
	win->width = (max_width < win->width) ? max_width : win->width;
	win->height = (max_height < win->height) ? max_height : win->height;
	return (SUCCESS);
}

static int	read_texture(void *mlx, t_tex *tex, char *tex_path)
{
	if (tex->img.img != NULL)
		return (TEX_DOUBLE_READ);
	if (ft_strlen(tex_path) <= 4 ||
		(ft_strncmp(tex_path + ft_strlen(tex_path) - 4, ".xpm", 5) != 0
			&& ft_strncmp(tex_path + ft_strlen(tex_path) - 4, ".png", 5) != 0))
		return (TEX_INVALID_EX);
	tex->img.img = mlx_xpm_file_to_image(mlx, tex_path,
													&tex->width, &tex->height);
	if (tex->img.img == NULL)
	{
		write(2, "Error\n", 7);
		perror(tex_path);
		return (FILE_OPEN_ERROR);
	}
	tex->img.addr = mlx_get_data_addr(tex->img.img, &tex->img.bits_per_pixel,
									&tex->img.line_length, &tex->img.endian);
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

static int	read_color(int *color, char *color_str)
{
	char	**rgb_str;
	int		rgb_nbr[3];
	int		ret;

	if (*color != NOT_READ)
		return (COLOR_DOUBLE_READ);
	if (!(rgb_str = ft_split(color_str, ',')))
		return (MALLOC_ERROR);
	if (!rgb_str[0] || !rgb_str[1] || !rgb_str[2] || rgb_str[3])
	{
		free_double_pointer(rgb_str);
		return (COLOR_NO_TWO_COMMAS);
	}
	ret = get_rgb_nbr(rgb_str, rgb_nbr);
	free_double_pointer(rgb_str);
	if (ret != SUCCESS)
		return (ret);
	*color = 256 * 256 * rgb_nbr[0] + 256 * rgb_nbr[1] + rgb_nbr[2];
	return (SUCCESS);
}

int			branch_size_tex_color(t_data *d, char **str)
{
	int flag;

	if (str[0] == NULL)
		flag = SUCCESS;
	else if (ft_strncmp(str[0], "R", 2) == 0 && str[1] && str[2] && !str[3])
		flag = read_window_size(d->mlx, &d->win, str[1], str[2]);
	else if (ft_strncmp(str[0], "NO", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d->mlx, &d->tex[NOUTH], str[1]);
	else if (ft_strncmp(str[0], "SO", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d->mlx, &d->tex[SOUTH], str[1]);
	else if (ft_strncmp(str[0], "WE", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d->mlx, &d->tex[WEST], str[1]);
	else if (ft_strncmp(str[0], "EA", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d->mlx, &d->tex[EAST], str[1]);
	else if (ft_strncmp(str[0], "S", 3) == 0 && str[1] && !str[2])
		flag = read_texture(d->mlx, &d->tex[SPRITE], str[1]);
	else if (ft_strncmp(str[0], "F", 2) == 0 && str[1] && !str[2])
		flag = read_color(&d->stage.color[FLOOR], str[1]);
	else if (ft_strncmp(str[0], "C", 2) == 0 && str[1] && !str[2])
		flag = read_color(&d->stage.color[CEIL], str[1]);
	else
		flag = NOT_ENOUGH_ELEMENT_OR_INVALID_SETTING;
	return (flag);
}
