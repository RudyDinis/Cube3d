NAME = Cube3d
LIBFT = utils/libft
SRC =	src/main.c src/temp/map.c \
		src/img/load_img.c \
		src/map/wall.c src/map/door.c \
		src/player/player.c src/player/view.c src/player/moove.c \
		src/eventListener/event.c src/eventListener/mouse.c \
		src/exit/exit.c src/exit/error_handler.c \
		src/parser/checker.c src/parser/check_id.c src/parser/check_map.c src/parser/check_xpm.c src/parser/parser_utils.c
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
run:
	./$(NAME)

re : fclean all
