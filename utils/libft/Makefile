NAME = libft.a

SRCS =	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c ft_memcpy.c ft_strlcpy.c ft_strlcat.c ft_toupper.c ft_tolower.c ft_atoi.c ft_strnstr.c ft_memcmp.c ft_memchr.c ft_strncmp.c ft_strchr.c ft_strrchr.c ft_calloc.c ft_strdup.c ft_substr.c ft_strjoin.c ft_memmove.c ft_strtrim.c ft_split.c ft_itoa.c ft_strmapi.c ft_striteri.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c
BONUS_SRCS = 

OBJS = $(SRCS:.c=.o)
BONUS_OBJS = $(BONUS_SRCS:.c=.o)

CC = gcc
CFLAGS = -Wall -Wextra -Werror -I .

so:
	@$(MAKE) fclean >/dev/null
	@$(MAKE) CFLAGS="$(CFLAGS) -fPIC" all >/dev/null
	@$(CC) -shared -o libft.so $(OBJS) $(BONUS_OBJS) 2>/dev/null || \
	$(CC) -shared -o libft.so -Wl,--whole-archive libft.a -Wl,--no-whole-archive;

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

bonus: $(BONUS_OBJS)
	ar rcs $(NAME) $(BONUS_OBJS)

all: $(NAME)

$(NAME): $(OBJS)
	ar rcs $(NAME) $(OBJS)

clean: 
	rm -f ${OBJS}

fclean:	clean
	rm -f $(NAME)

re: fclean all
