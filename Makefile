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
			heap_utils					\
			merge_heaps					\
			add_new_heap_free_blocks	\
			add_heap_pos_free_blocks	\
			find_heap					\
			initialize_new_heap			\

SRCS_HEAP = $(addprefix heap_related/, $(SRC_HEAP))

SRC =	$(SRCS_BLOCK)		\
		$(SRCS_HEAP)		\
		malloc				\
		realloc				\
		free				\

OBJS = $(SRCS:%.c=%.o)

######################### HEADERS ##########################

HEADERS = $(DIR_LIBFT)/libft.h
INCLUDE = -I $(DIR_INCLUDE) -I $(DIR_LIBFT)

####################### COMPILATION ########################

CC = gcc
CFLAGS = -Wall -Werror -Wextra
LIBFLAGS = -fPIC -shared

########################## RULES ###########################

ifdef BONUS
			DIR_INCLUDE = $(DIR_MALLOC)/bonus/include
			HEADER += $(DIR_INCLUDE)/libft_malloc_bonus.h
			SRCS =	$(addsuffix _bonus.c, $(addprefix $(DIR_SRCS_BONUS)/, $(SRC)))	\
					$(DIR_SRCS_BONUS)/show_mem_hexdump/show_mem_hexdump_bonus.c		\
					$(DIR_SRCS_BONUS)/show_mem_hexdump/display_hexa_format_bonus.c
			CFLAGS += -pthread

else
			DIR_INCLUDE = $(DIR_MALLOC)/mandatory/include
			HEADER += $(DIR_INCLUDE)/libft_malloc.h
			SRCS =	$(addsuffix .c, $(addprefix $(DIR_SRCS_MANDATORY)/, $(SRC)))	\
					$(DIR_SRCS_MANDATORY)/show_mem/show_alloc_mem.c
endif

%.o: %.c
	$(CC) $(CFLAGS) $(LIBFLAGS) $(INCLUDE) -c $< -o $@

all: $(NAME)

$(NAME): $(LIBFT) $(HEADERS) $(OBJS)
	$(CC) $(CFLAGS) $(LIBFLAGS) $(OBJS) -o $(NAME)
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
