#************************************#
#			SET HOSTTYPE			 #
#************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

######################### DIRS ##########################

DIR_MALLOC = libft_malloc

DIR_MALLOC_SRCS = $(DIR_MALLOC)/srcs

DIR_MALLOC_INCLUDE = $(DIR_MALLOC)/include

DIR_LIBFT = libft

####################### LIBRARIES #######################

NAME = $(DIR_MALLOC)/libft_malloc_$(HOSTTYPE).so

SYMLINK_LIB = libft_malloc.so

LIBFT = $(DIR_LIBFT)/libft.a

######################### SRCS ##########################

SRC_BLOCK =	get_avail_block.c		\
			add_free_block.c		\
			add_alloc_block.c		\
			delete_block.c			\
			extend_block.c			\
			shrink_alloc_block.c	\
			shrink_free_block.c		\

SRCS_BLOCK = $(addprefix block_related/, $(SRC_BLOCK))

SRC_HEAP =	add_heap.c			\
			allocate_heap.c		\
			create_new_heap.c	\
			heap_utils.c		\
			merge_heaps.c		\

SRCS_HEAP = $(addprefix heap_related/, $(SRC_HEAP))

SRCS_SHOW_MEM =	show_mem/show_alloc_mem.c

SRC =	$(SRCS_BLOCK)		\
		$(SRCS_HEAP)		\
		$(SRCS_SHOW_MEM)	\
		malloc.c			\
		realloc.c			\
		free.c				\

SRCS = $(addprefix $(DIR_MALLOC_SRCS)/, $(SRC))	\

OBJS = $(SRCS:%.c=%.o)

######################### HEADERS ##########################

HEADERS = $(DIR_MALLOC_INCLUDE)/libft_malloc.h $(DIR_LIBFT)/libft.h

INCLUDE = -I $(DIR_MALLOC_INCLUDE) -I $(DIR_LIBFT)

####################### COMPILATION ########################

CC = gcc

CFLAGS = -Wall -Werror -Wextra -g

LIBFLAGS = -fPIC -shared

########################## RULES ###########################

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(HEADERS) main.o $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) -o $(NAME)
	rm -f $(SYMLINK_LIB)
	ln -s $(NAME) $(SYMLINK_LIB)
	$(CC) $(CFLAGS) main.o -L. -L$(DIR_LIBFT) -lft_malloc -lft -o malloc

$(LIBFT):
	make -C libft -s

clean:
	make clean -C libft
	rm -rf $(OBJS) main.o

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME) $(SYMLINK_LIB) malloc

re: fclean all

.PHONY: all clean fclean re
