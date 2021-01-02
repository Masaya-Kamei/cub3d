SRCDIR		= ./srcs/
SRCNAME		= cub3d.c read_conf_file.c read_size_tex_color.c read_map.c \
			  check_closed_map.c draw_wall.c draw_sprite.c deal_key.c \
		 	  save_bmp.c get_next_line.c
SRCS		= $(addprefix $(SRCDIR), $(SRCNAME))
OBJS		= $(SRCS:.c=.o)
INCLUDE		= -I./includes/
NAME		= cub3D
CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
RM			= rm -f
LIBDIR		= ./libft
LIBNAME 	= libft.a
LIB			= $(LIBDIR)/$(LIBNAME)
LIBXDIR		= ./minilibx
LIBXNAME	= libmlx.dylib
LIBX		= $(LIBXDIR)/$(LIBXNAME)

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

# libmlx.dylib があると、$(LIBXNAME)が実行されない
$(NAME)	:	$(LIBNAME) $(LIBXNAME) $(OBJS)
			cp $(LIBX) ./
			$(CC) $(CFLAGS)　$(INCLUDE) $(LIB) $(LIBXNAME) $(OBJS) -o $(NAME)
# $(CC) $(CFLAGS)　$(INCLUDE) $(LIB) $(LIBXNAME) -g -fsanitize=address $(OBJS) -o $(NAME)

$(LIBNAME):
			make -C $(LIBDIR)

$(LIBXNAME):
			make -C $(LIBXDIR)

clean	:
			$(RM) $(OBJS)
			make clean -C $(LIBDIR)
			make clean -C $(LIBXDIR)

fclean	:	clean
			$(RM) $(NAME)
			$(RM) $(LIBXNAME)
			make fclean -C $(LIBDIR)

re		:	fclean all

.PHONY	:	all clean fclean re $(LIBNAME) $(LIBXNAME)
