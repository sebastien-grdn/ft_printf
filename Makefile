# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: sg9031 <sg9031@gmail.com>                  +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/02/03 21:28:31 by sg9031            #+#    #+#              #
#    Updated: 2021/02/03 22:06:01 by sg9031           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

LIB_DIR		= libft
LIBFT_SRCS	= ft_memcpy.c ft_strchr.c ft_strdup.c ft_strlcat.c ft_strlcpy.c\
			  ft_strrchr.c ft_strlen.c ft_strlcpy.c ft_strnstr.c\
			  ft_strncmp.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			  ft_isprint.c ft_toupper.c ft_tolower.c ft_isdigit.c ft_memmove.c \
			  ft_memccpy.c ft_memset.c ft_bzero.c ft_memcmp.c ft_memchr.c ft_calloc.c\
			  ft_atoi.c ft_substr.c ft_strjoin.c ft_strtrim.c ft_split.c\
			  ft_itoa.c ft_strmapi.c ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c\
			  ft_putnbr_fd.c
LIBFT_OBJS	= ${addprefix ${LIB_DIR}/, ${LIBFT_SRCS:.c=.o}}

PRINTF_DIR	= srcs
PRINTF_SRCS	= ft_printf.c
PRINTF_OBJS = ${addprefix ${PRINTF_DIR}/, ${PRINTF_SRCS:.c=.o}}

CC			= gcc
CFLAGS		= -Wall -Wextra -Werror
NAME		= printf.a
RM			= rm -f

.c.o:
			${CC} ${CFLAGS} -c -I./includes $< -o ${<:.c=.o}

${NAME}:	${LIBFT_OBJS} ${PRINTF_OBJS}
			ar -rcs $@ $^

all:		${NAME}

clean:
			${RM} ${LIBFT_OBJS} ${PRINTF_OBJS}

fclean:		clean
			${RM} ${NAME}

re:			fclean all

.PHONY:		all clean fclean re