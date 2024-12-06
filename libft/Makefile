# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsauvain <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/12 15:21:43 by jsauvain          #+#    #+#              #
#    Updated: 2024/12/06 12:55:35 by jsauvain         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS = ft_bzero.c ft_isalnum.c ft_isalpha.c ft_isascii.c ft_isdigit.c ft_isprint.c \
		ft_memcpy.c ft_memmove.c ft_memset.c ft_strlcpy.c ft_strlcat.c ft_strlen.c \
		ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c ft_strncmp.c ft_memchr.c \
		ft_memcmp.c ft_strnstr.c ft_atoi.c ft_strdup.c ft_calloc.c ft_substr.c \
		ft_strjoin.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
		ft_strtrim.c ft_strmapi.c ft_striteri.c ft_itoa.c ft_split.c ft_format.c  \
		ft_printf.c  ft_putchar.c  ft_putnbr.c  ft_putstr.c  low_hexa.c  \
		put_hexa_ptr.c  to_find.c  up_hexa.c ft_lstnew.c ft_lstadd_front.c \
		ft_lstsize.c ft_lstlast.c ft_lstadd_back.c ft_lstdelone.c ft_lstclear.c \
		ft_lstiter.c ft_lstmap.c

CC = gcc

CCFLAGS = -Wall -Wextra -Werror

OBJS = ${SRCS:.c=.o}

NAME = libft.a

RM = rm -f

AR = ar rcs

all: $(NAME)

clean:
		${RM} ${OBJS}

.c.o:
	${CC} ${CFLAGS} -c $< -o ${<:.c=.o}

fclean: clean
		${RM} $(NAME)

$(NAME): ${OBJS}
		${AR} $(NAME) ${OBJS}


re: fclean all

.PHONY: all clean fclean re
