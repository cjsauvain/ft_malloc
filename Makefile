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

DIR_LIBFT = libft/

LIBFT = $(DIR_LIBFT)libft.a

SRC =	create_new_heap.c		\
		malloc.c				\
		get_avail_block.c		\
		heap_utils.c			\
		free.c					\
		main.c					\
		realloc.c				\
		show_alloc_mem.c		\
		block_utils.c			\
		block_management.c		\
		merge_heaps.c			\
		shrink_alloc_block.c	\
		shrink_free_block.c		\
		extend_block.c			\
		add_free_block.c		\

SRCS = $(addprefix $(DIR_MALLOC), $(SRC))	\

OBJS = $(SRCS:%.c=%.o)

HEADER = $(DIR_MALLOC)libft_malloc.h $(DIR_LIBFT)libft.h

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

LIBFLAGS = -fPIC -shared

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(HEADER) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) -o $(NAME)
	rm -f $(SYMLINK_LIB)
	ln -s $(NAME) $(SYMLINK_LIB)
	$(CC) $(CFLAGS) -L$(DIR_MALLOC) -L$(DIR_LIBFT) -lft_malloc_$(HOSTTYPE) -lft -o malloc

$(LIBFT):
	make -C libft

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME) $(SYMLINK_LIB) malloc

re: fclean all

.PHONY: all clean fclean re
