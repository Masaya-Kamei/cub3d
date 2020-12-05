SRCS	= ./cub3d.c ./read_cub.c ./draw_wall.c
OBJS	= $(SRCS:.c=.o)
INCLUDE	= -I./
NAME	= cub3D
CC		= gcc
CFLAGS	= -Wall -Wextra -Werror
RM		= rm -f
LIBDIR	= ./libft
LIBNAME = libft.a
LIB		= $(LIBDIR)/$(LIBNAME)
LIBXDIR	= ./minilibx
LIBXNAME	= libmlx.dylib
LIBX	= $(LIBXDIR)/$(LIBXNAME)

all		:	$(NAME)

.c.o	:
			$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(<:.c=.o)

$(NAME)	:	$(LIBNAME) $(LIBXNAME) $(OBJS)
			cp $(LIBX) ./
			$(CC) $(CFLAGS) $(INCLUDE) $(LIB) $(LIBXNAME) $(OBJS) -o $(NAME)

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
			make fclean -C $(LIBDIR)
			make fclean -C $(LIBXDIR)

re		:	fclean all

.PHONY	:	all clean fclean re
