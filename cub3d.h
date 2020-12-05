/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:18:37 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/05 19:22:55 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

#include "minilibx/mlx.h"
#include "libft/libft.h"
#include <unistd.h>
#include <string.h>
#include <math.h>
#include <stdio.h>

# define PI 3.14159
# define FIRST 1
# define NOT_FIRST 0
# define ANSWER -1
// typedef struct	s_point {
// 	double		x;
// 	double		y;
// }				t_point;

// typedef	struct	s_line {
// 	double		begin_x;
// 	double		begin_y;
// 	double		angle;
// }				t_line;

// typedef struct	s_player {
// 	t_line		ray;
// 	double		x;
// 	double		y;
// 	double		angle;
// }				t_player;

typedef struct	s_win {
	void		*win;
	int			width;
	int			height;
}				t_win;

typedef struct	s_stage {
	char		**map;
	int			c_color;
	int			f_color;
	char		*n_texture;
	char		*s_texture;
	char		*e_texture;
	char		*w_texture;
}				t_stage;


typedef struct	s_vector {
	double		x;
	double		y;
}				t_vector;

typedef struct	s_ray {
	double		x;
	double		y;
	t_vector	deltaDist;
	t_vector	sideDist;
	t_vector	tip;
}				t_ray;

typedef struct	s_player {
	t_vector	pos;
	t_vector	dir;
	t_vector	plane;
	// t_ray		ray;
	// t_vector	map;
}				t_player;

typedef struct	s_data {
	void		*mlx;
	t_win		win;
	t_stage 	stage;
	t_player 	player;
}				t_data;


int		read_cub(t_data *d);
int		draw_wall(t_data *d);

// typedef struct  s_data {
//     void        *img;
//     char        *addr;
//     int         bits_per_pixel;
//     int         line_length;
//     int         endian;
// }               t_data;

// typedef struct  s_vars {
//         void    *mlx;
//         void    *win;
// }               t_vars;

#endif
