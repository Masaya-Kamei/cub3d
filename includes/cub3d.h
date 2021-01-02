/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:18:37 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/02 14:46:25 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# include "../minilibx/mlx.h"
# include "../libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# define MAX(x, y) (x > y) ? x : y
# define BUFFER_SIZE 1000
# define ESC_KEY 53
# define W_KEY 13
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define LEFT_KEY 123
# define RIGHT_KEY 124
# define NOUTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4
# define FLOOR 5
# define CEIL 6
# define OUT_OF_RANGE -1
# define PI 3.14159265359
# define MOVE 0.25
# define RADIAN 0.1
# define VIEW_ANGLE 33.4248111826
# define SUCCESS 0
# define MALLOC_ERROR 1
# define FILE_OPEN_ERROR 2
# define NOT_ENOUGH_ELEMENT 3
# define GNL_ERROR 4
# define R_DOUBLE_READ 6
# define R_NOT_NUMBER 7
# define R_OUT_OF_RANGE 8
# define NOT_ENOUGH_ELEMENT_OR_INVALID_SETTING 9
# define TEX_DOUBLE_READ 10
# define TEX_INVALID_EXTENSION 11
# define COLOR_DOUBLE_READ 13
# define COLOR_NOT_TWO_COMMAS 14
# define COLOR_NOT_NUMBER 15
# define COLOR_OUT_OF_RANGE 16
# define NOT_END_MAP 17
# define SMALL_MAP 18
# define PLAYER_DOUBLE 19
# define INVALID_CHARACTER_IN_MAP 20
# define NOT_DETECTED_PLAYER 21
# define DETECTED_SPACE_IN_ROOM 22
# define NOT_ARROUND_WALL 23
# define COMMAND_LINE_ERROR 24
# define NOT_CUB_FILE 25
# define FILE_SIZE 0
# define OFFSET_TO_DATA 1
# define INFO_HEADER_SIZE 2
# define PLANES 3
# define COLOR 4
# define DATA_SIZE 5
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define BMP_HEADER_SIZE (BMP_FILE_HEADER_SIZE + BMP_INFO_HEADER_SIZE)
# define TEX_HEIGHT 0
# define WIN_HALF_HEIGHT 1
# define TEX_START 2
# define TEX_END 3
# define TEX_X 4
# define TEX_Y 5

typedef struct		s_img {
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	int				width;
	int				height;
}					t_img;
typedef struct		s_vector {
	double			x;
	double			y;
}					t_vector;

typedef struct		s_sprite {
	double			dist_to_sprite;
	double			ratio_x;
}					t_sprite;

typedef struct		s_ray {
	double			x;
	double			y;
	int				hit_side;
	double			dist_to_wall;
	t_vector		delta_dist;
	t_vector		side_dist;
	t_vector		tip;
	t_list			*sprite_lst;
}					t_ray;

typedef struct		s_win {
	void			*win;
	int				width;
	int				height;
}					t_win;

typedef struct		s_stage {
	char			**map;
	int				height;
	int				width;
	unsigned int	f_color;
	unsigned int	c_color;
}					t_stage;

typedef struct		s_player {
	t_vector		pos;
	t_vector		dir;
	t_vector		plane;
}					t_player;

typedef struct		s_tex {
	t_img			img;
	int				width;
	int				height;
}					t_tex;
typedef struct		s_data {
	void			*mlx;
	t_win			win;
	t_stage			stage;
	t_player		player;
	t_ray			ray;
	t_img			img;
	t_tex			tex[5];
	char			error_msg[30][50];
}					t_data;

void				free_double_pointer(char **str);
void				finish_program(t_data *d, int error_nbr);
void				finish_reading_conf_file(t_data *d, int fd, int error_nbr);
void				read_conf_file(t_data *d, char *conf_file);
int					branch_size_tex_color(t_data *d, char **str,
													char *read_flags);
t_list				*add_map_lines_to_list(t_data *d, int fd);
void				create_map_from_list(t_data *d, int fd,
											t_list *lst, t_stage *stage);
void				check_characters_of_map(t_data *d, int fd,
													int *player_flag);
void				check_closed_map(t_data *d, int fd, t_stage stage);
void				draw_to_img(t_data *d);
void				add_sprite_to_list(t_data *d, t_ray *ray, t_player p);
void				draw_sprite_one_line(t_data *d, int draw_x,
													t_sprite sp, t_tex tex);
int					deal_key(int key, t_data *d);
void				save_bmp(t_data *d, t_img img);
int					get_next_line(int fd, char **line);

#endif
