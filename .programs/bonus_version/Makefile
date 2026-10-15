# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tschwab <tschwab@student.42lausanne.ch>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2026/10/15 14:27:32 by tschwab           #+#    #+#              #
#    Updated: 2026/10/15 14:27:33 by tschwab          ###   ########.ch        #
#                                                                              #
# **************************************************************************** #

NAME		= gnl_bonus

SOURCES		= main_bonus.c \
			main_utils_bonus.c \
			get_next_line_bonus.c \
			get_next_line_utils_bonus.c

HEADERS		= get_next_line_bonus.h \
			main_bonus.h

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