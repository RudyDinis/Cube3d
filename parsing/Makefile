NAME = parser
CC = cc
CFLAGS = -Wall -Wextra -Werror
AR = ar rcs
RM = rm -rf
OBJ_DIR = obj

SRC = checker.c check_id.c check_map.c check_xpm.c parser_utils.c

OBJ = $(SRC:%.c=$(OBJ_DIR)/%.o)
HEADER = parsing.h

all: $(NAME)

$(NAME): $(OBJ) $(HEADER)
	make -C ../libft
	$(CC) $(CFLAGS) $(OBJ) -L../libft -lft -o $@

$(OBJ_DIR)/%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	make -C ../libft clean
	$(RM) $(OBJ_DIR)

fclean: clean
	make -C ../libft fclean
	$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re
