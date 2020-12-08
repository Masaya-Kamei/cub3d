/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:18:37 by mkamei            #+#    #+#             */
/*   Updated: 2020/12/06 21:07:49 by mkamei           ###   ########.fr       */
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
#include <time.h>
#include <sys/time.h>

# define ESC 53
# define UP 126
# define DOWN 125
# define RIGHT 124
# define LEFT 123


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

typedef struct  s_img {
	void		*img;
	char		*addr;
	int			bits_per_pixel;
	int			line_length;
	int			endian;
}				t_img;

typedef struct	s_win {
	void		*win;
	int			width;
	int			height;
}				t_win;

typedef struct	s_texture {
	// char		*path;
	// void		*img;
	t_img		img;
	int			width;
	int			height;
}				t_texture;

typedef struct	s_stage {
	char		**map;
	int			c_color;
	int			f_color;
	t_texture	n_tex;
	t_texture	s_tex;
	t_texture	e_tex;
	t_texture	w_tex;
}				t_stage;


typedef struct	s_vector {
	double		x;
	double		y;
}				t_vector;

typedef struct	s_ray {
	double		x;
	double		y;
	int			hitSide;
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
	t_img		img;
	// t_textures	tex;
}				t_data;


int		read_cub(t_data *d);
int		draw_to_win(t_data *d);

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
