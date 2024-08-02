#************************************#
#			SET HOSTTYPE			 #
#************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

#************************************#
#			VARIABLES				 #
#************************************#

NAME = libft_malloc/libft_malloc_$(HOSTTYPE).so

SYMLINK_LIB = libft_malloc.so

DIR_MALLOC = libft_malloc/

SRC =	create_new_heap.c	\
		ft_malloc.c		\
		get_avail_block.c	\
		heap_utils.c		\

SRCS = $(addprefix $(DIR_MALLOC), $(SRC))

OBJS = $(SRCS:%.c=%.o)

CC = gcc

CFLAGS = -Wall -Werror -Wextra -Wpadded -g

LIBFLAGS = -shared

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	make -C libft
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) -o $(NAME)
	rm -f $(SYMLINK_LIB)
	ln -s $(NAME) $(SYMLINK_LIB)
	$(CC) $(CFLAGS) main.c -L$(DIR_MALLOC) -lft_malloc_$(HOSTTYPE) -o malloc

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	make fclean -C libft
	rm -rf $(NAME) $(SYMLINK_LIB)

re: fclean all

.PHONY: all clean fclean re
