NAME = Cube3d
LIBFT = utils/libft
SRC = utils/gnl/get_next_line_utils.c utils/gnl/get_next_line.c \
		src/main.c src/temp/map.c \
		src/img/load_img.c \
		src/player/wall.c src/player/door.c \
		src/player/player.c src/player/view.c src/player/moove.c \
		src/eventListener/event.c \
		src/exit/exit.c src/exit/error_handler.c
OBJ := $(SRC:%.c=%.o)

CC = cc -std=c11
CFLAGS = -Wall -Wextra -Werror -I . -Imlx_linux

all: $(NAME)

$(NAME): $(OBJ)
	make -C ${LIBFT}
	$(CC) $(CFLAGS) $(OBJ) ${LIBFT}/libft.a -Lmlx_linux -lmlx_Linux -L/usr/lib -lXext -lX11 -lm -lz -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make clean -C ${LIBFT}
	rm -f $(OBJ)

fclean: clean
	make fclean -C ${LIBFT}
	rm -f $(NAME)

re : fclean all