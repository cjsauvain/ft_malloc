#************************************#
#			SET HOSTTYPE			 #
#************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

######################### DIRS ##########################

DIR_MALLOC = libft_malloc
DIR_SRCS_MANDATORY = $(DIR_MALLOC)/mandatory/srcs
DIR_SRCS_BONUS = $(DIR_MALLOC)/bonus/srcs
DIR_INCLUDE_MANDATORY = $(DIR_MALLOC)/mandatory/include
DIR_INCLUDE_BONUS = $(DIR_MALLOC)/bonus/include
DIR_LIBFT = libft

####################### LIBRARIES #######################

NAME = $(DIR_MALLOC)/libft_malloc_$(HOSTTYPE).so
SYMLINK_LIB = libft_malloc.so
LIBFT = $(DIR_LIBFT)/libft.a

######################### FILES ##########################

SRC_BLOCK =	get_avail_block		\
			add_free_block		\
			add_alloc_block		\
			delete_block		\
			extend_block		\
			shrink_alloc_block	\
			shrink_free_block	\

SRCS_BLOCK = $(addprefix block_related/, $(SRC_BLOCK))

SRC_HEAP =	add_heap					\
			create_new_heap				\
			merge_heaps					\
			add_new_heap_free_blocks	\
			add_heap_pos_free_blocks	\
			find_heap					\
			initialize_new_heap			\
			select_heap					\
			get_heap_group				\
			check_heap_state			\
			check_heap_left				\

SRCS_HEAP = $(addprefix heap_related/, $(SRC_HEAP))

SRC =	$(SRCS_BLOCK)		\
		$(SRCS_HEAP)		\
		malloc				\
		realloc				\
		free				\

OBJS = $(SRCS:%.c=%.o)

######################### HEADERS ##########################

HEADERS = $(DIR_LIBFT)/libft.h
INCLUDE = -I $(DIR_LIBFT)

####################### COMPILATION ########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g
LIBFLAGS = -fPIC -shared
LIBFT_LINK = -Llibft -lft

########################## RULES ###########################

ifdef BONUS
			INCLUDE +=	-I $(DIR_INCLUDE_BONUS)
			HEADERS +=	$(DIR_INCLUDE_BONUS)/libft_malloc_bonus.h	\
						$(DIR_INCLUDE_BONUS)/defines_bonus.h		\
						$(DIR_INCLUDE_BONUS)/struct_bonus.h
			SRCS =	$(addsuffix _bonus.c, $(addprefix $(DIR_SRCS_BONUS)/, $(SRC)))	\
					$(DIR_SRCS_BONUS)/show_mem_hexdump/show_mem_hexdump_bonus.c		\
					$(DIR_SRCS_BONUS)/show_mem_hexdump/display_hexa_format_bonus.c
			CFLAGS += -pthread

else
			INCLUDE +=	-I $(DIR_INCLUDE_MANDATORY)
			HEADERS +=	$(DIR_INCLUDE_MANDATORY)/libft_malloc.h	\
						$(DIR_INCLUDE_MANDATORY)/defines.h			\
						$(DIR_INCLUDE_MANDATORY)/struct.h
			SRCS =	$(addsuffix .c, $(addprefix $(DIR_SRCS_MANDATORY)/, $(SRC)))	\
					$(DIR_SRCS_MANDATORY)/show_mem/show_alloc_mem.c
endif

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) $(LIBFT_LINK) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) $(LIBFT) -o $(NAME)
	rm -f $(SYMLINK_LIB)
	ln -s $(NAME) $(SYMLINK_LIB)

bonus:
	make BONUS=1

$(LIBFT):
	make -C libft -s

clean:
	make clean -C libft
	rm -rf $(OBJS)

cleanb:
	make clean BONUS=1

fclean: clean cleanb
	rm -rf libft/libft.a
	rm -rf $(NAME) $(SYMLINK_LIB) malloc

re: fclean all

.PHONY: all clean fclean re
