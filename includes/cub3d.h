/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mkamei <mkamei@student.42tokyo.jp>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/30 11:18:37 by mkamei            #+#    #+#             */
/*   Updated: 2021/01/05 19:50:47 by mkamei           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUB3D_H
# define CUB3D_H

# if __linux__
#  include "../minilibx-linux/mlx.h"
# else
#  include "../minilibx/mlx.h"
# endif
# include "../libft/libft.h"
# include <unistd.h>
# include <string.h>
# include <math.h>
# include <stdlib.h>
# include <fcntl.h>
# include <stdio.h>

# if __linux__
#  define ESC_KEY 65307
#  define W_KEY 119
#  define A_KEY 97
#  define S_KEY 115
#  define D_KEY 100
#  define LEFT_KEY 65361
#  define RIGHT_KEY 65363
#  define DESTROY_EVENT 33
# else
#  define ESC_KEY 53
#  define W_KEY 13
#  define A_KEY 0
#  define S_KEY 1
#  define D_KEY 2
#  define LEFT_KEY 123
#  define RIGHT_KEY 124
#  define DESTROY_EVENT 17
# endif
# define KEYDOWN_EVENT 2
# define FOCUSIN_EVENT 9
# define NOUTH 0
# define SOUTH 1
# define WEST 2
# define EAST 3
# define SPRITE 4
# define FLOOR 0
# define CEIL 1
# define BUFFER_SIZE 1000
# define NOT_READ -1
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
# define R_DOUBLE_READ 5
# define R_NOT_NUMBER 6
# define R_OUT_OF_RANGE 7
# define NOT_ENOUGH_ELEMENT_OR_INVALID_SETTING 8
# define TEX_DOUBLE_READ 9
# define TEX_INVALID_EX 10
# define COLOR_DOUBLE_READ 11
# define COLOR_NOT_TWO_COMMAS 12
# define COLOR_NOT_NUMBER 13
# define COLOR_OUT_OF_RANGE 14
# define NOT_END_MAP 15
# define PLAYER_DOUBLE_READ 16
# define INVALID_CHARACTER_IN_MAP 17
# define NOT_DETECTED_PLAYER 18
# define DETECTED_SPACE_IN_MAP 19
# define NOT_SURROUNDED_WALL 20
# define COMMAND_LINE_ERROR 21
# define NOT_CUB_FILE 22
# define INVALD_ELEMENT_OR_INVALID_CHARACTER 23
# define FILE_SIZE 0
# define OFFSET_TO_DATA 1
# define INFO_HEADER_SIZE 2
# define PLANES 3
# define COLOR 4
# define DATA_SIZE 5
# define BMP_FILE_HEADER_SIZE 14
# define BMP_INFO_HEADER_SIZE 40
# define BMP_HEADER_SIZE 54
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
	int				color[2];
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
	t_img			img;
	t_tex			tex[5];
	char			error_msg[30][50];
	int				fd;
}					t_data;

void				free_double_pointer(char **str);
void				finish_program(t_data *d, int error_nbr);
void				read_conf_file(t_data *d, char *conf_file);
int					branch_size_tex_color(t_data *d, char **str);
t_list				*add_map_lines_to_list(t_data *d, int fd);
int					check_characters_of_map_line(t_player *player,
															char *line, int y);
int					add_map_line_to_list(t_list **lst, char *line);
int					create_map_from_list(t_list *lst, t_stage *stage);
int					check_closed_map(t_player player, t_stage stage);
void				draw_to_img(t_data *d);
void				add_sprite_to_list(t_data *d, t_ray *ray, t_player p);
void				draw_sprite_one_line(t_data *d, int draw_x,
													t_sprite sp, t_tex tex);
int					deal_key_by_keydown(int key, t_data *d);
void				destroy_display(t_data *d);
int					finish_program_by_destory(t_data *d);
int					put_image_to_window_by_focusin(t_data *d);
void				save_bmp(t_data *d, t_img img);
int					get_next_line(int fd, char **line);

#endif
