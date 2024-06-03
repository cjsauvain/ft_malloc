NAME = malloc

SRC = ft_malloc.c

SRCS = $(addprefix srcs/, $SRC)

OBJS = $(SRCS:%.c=%.o)

OBJS_PATH = objects

HEADER = malloc.h

INCLUDE = -I $(HEADER)

CC = gcc

CFLAGS = -Wall -Wextra -Werror -g

%.o: %.c $(HEADER)
	$(CC) $(CFLAGS) $(INCLUDE) -c $< -o $(addprefix $(OBJS_PATH)/, $@)

objects:
	mkdir $(OBJS_PATH)

all: objects $(NAME)

$(NAME): $(OBJS)
	$(CC) $(OBJS) -o $(NAME)

clean:
	rm $(OBJS)

fclean: clean
	rm $(NAME)

re: fclean all

.PHONY: all clean fclean re
