#************************************#
#			SET HOSTTYPE			 #
#************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

######################### DIRS ##########################

DIR_MALLOC = libft_malloc
DIR_SRCS = $(DIR_MALLOC)/srcs
DIR_INCLUDE_MALLOC = $(DIR_MALLOC)/include
DIR_LIBFT = libft

####################### LIBRARY #######################

NAME = $(DIR_MALLOC)/libft_malloc_$(HOSTTYPE).so
SYMLINK_LIB = libft_malloc.so
LIBFT = $(DIR_LIBFT)/libft.a

######################### SRCS/OBJS ##########################

SRC_BLOCK =	get_avail_block.c		\
			add_free_block.c		\
			add_alloc_block.c		\
			delete_block.c			\
			delete_whole_block.c	\
			delete_partially.c		\
			extend_block.c			\
			shrink_alloc_block.c	\
			shrink_free_block.c		\

SRCS_BLOCK = $(addprefix block/, $(SRC_BLOCK))

SRC_HEAP =	add_heap.c					\
			create_new_heap.c			\
			merge_heaps.c				\
			add_new_heap_free_blocks.c	\
			add_heap_pos_free_blocks.c	\
			find_heap.c					\
			initialize_new_heap.c		\
			select_heap.c				\
			get_heap_group.c			\
			check_heap_state.c			\
			check_heap_left.c			\

SRCS_HEAP = $(addprefix heap/, $(SRC_HEAP))

SRC_SHOW_MEM =	show_alloc_mem.c		\
				show_mem_hexdump.c		\
				display_hexa_format.c	\

SRCS_SHOW_MEM = $(addprefix show_mem/, $(SRC_SHOW_MEM))

SRC =	$(SRCS_BLOCK)		\
		$(SRCS_HEAP)		\
		$(SRCS_SHOW_MEM)	\
		malloc.c			\
		realloc.c			\
		free.c				\

SRCS =	$(addprefix $(DIR_SRCS)/, $(SRC))

OBJS_DIR = objects
OBJS = $(subst $(DIR_SRCS)/,,$(SRCS:%.c=$(OBJS_DIR)/%.o))

######################### HEADERS ##########################

HEADERS =	$(DIR_LIBFT)/libft.h 					\
			$(DIR_INCLUDE_MALLOC)/libft_malloc.h	\
INCLUDE =	-I $(DIR_LIBFT)				\
			-I $(DIR_INCLUDE_MALLOC)	\

####################### COMPILATION ########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -pthread -g
SHAREDLIB_FLAGS = -fPIC -shared
LIBFT_LINK = -Llibft -lft

########################## RULES ###########################

$(OBJS_DIR)/%.o: $(SRCS_DIR)/%.c $(HEADERS)
	$(CC) $(CFLAGS) $(SHAREDLIB_FLAGS) $(INCLUDE) $(LIBFT_LINK) -c $< -o $@

all: $(NAME)

$(OBJS_DIR):
	@mkdir -p	$(OBJS_DIR)/block_related	\
				$(OBJS_DIR)/heap_related	\
				$(OBJS_DIR)/show_mem		\

$(NAME): $(LIBFT) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(SHAREDLIB_FLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	rm -f $(SYMLINK_LIB)
	ln -s $(NAME) $(SYMLINK_LIB)

$(LIBFT):
	make -C libft -s

clean:
	make clean -C libft
	rm -rf $(OBJS)

fclean: clean
	rm -rf libft/libft.a
	rm -rf $(NAME) $(SYMLINK_LIB)

re: fclean all

.PHONY: all clean fclean re
