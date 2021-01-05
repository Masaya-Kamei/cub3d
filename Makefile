SRCDIR		= ./srcs/
SRCNAME		= cub3d.c read_conf_file.c read_size_tex_color.c read_map.c \
			  check_closed_map.c draw_wall.c draw_sprite.c deal_key.c \
		 		save_bmp.c get_next_line.c others.c
SRCS		= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS		= $(SRCS:.c=.o)
INCLUDE		= -I./includes/
NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
LIBFTDIR	= ./libft
LIBFTNAME 	= libft.a
LIBFT		= $(LIBFTDIR)/$(LIBFTNAME)
UNAME 		= $(shell uname)
ifeq ($(UNAME),Linux)
	LIBMLXDIR	= ./minilibx-linux
	LIBMLXNAME	= libmlx_Linux.a
	LIBMLX		= $(LIBMLXDIR)/$(LIBMLXNAME)
	LINK		= -lXext -lX11 -lm
else
	LIBMLXDIR	= ./minilibx
	LIBMLXNAME	= libmlx.dylib
	LIBMLX		= $(LIBMLXDIR)/$(LIBMLXNAME)
	LINK		=
endif

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(LIBFTNAME) $(LIBMLXNAME) $(OBJS)
			cp $(LIBMLX) ./
			$(CC) $(CFLAGS) $(INCLUDE) $(OBJS) $(LIBFT) $(LIBMLXNAME) $(LINK) -o $(NAME)

$(LIBFTNAME):
			make -C $(LIBFTDIR)

$(LIBMLXNAME):
			make -C $(LIBMLXDIR)

clean	:
			$(RM) $(OBJS)
			make clean -C $(LIBFTDIR)
			make clean -C $(LIBMLXDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBMLXNAME)
			$(RM) capture.bmp
			make fclean -C $(LIBFTDIR)

re		:	fclean all

.PHONY	:	all clean fclean re $(LIBFTNAME) $(LIBMLXNAME)
