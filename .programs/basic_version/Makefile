# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschwab <tschwab@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/15 14:27:08 by tschwab           #+#    #+#              #
#    Updated: 2026/10/15 14:27:09 by tschwab          ###   ########.ch        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl

SOURCES		= main.c \
			get_next_line.c \
			get_next_line_utils.c

HEADERS		= get_next_line.h

OBJECTS		= ${SOURCES:.c=.o}

BUFFER_SIZE	?= 42

CC			= cc
CFLAGS		= -Wall -Wextra -Werror -D BUFFER_SIZE=${BUFFER_SIZE}

RM			= rm -f

all: ${NAME}

${NAME}: ${OBJECTS}
	${CC} ${CFLAGS} ${OBJECTS} -o ${NAME}

%.o: %.c ${HEADERS}
	${CC} ${CFLAGS} -c $< -o $@

clean:
	${RM} ${OBJECTS}

fclean: clean
	${RM} ${NAME}

re: fclean all

.PHONY: all clean fclean re