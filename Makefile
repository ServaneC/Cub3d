# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: schene <schene@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/05 10:13:06 by schene            #+#    #+#              #
#    Updated: 2020/02/14 13:37:17 by schene           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	srcs/parsing/parsing.c \
				srcs/parsing/parsing_utils.c \
				srcs/parsing/parsing_map.c \
				srcs/parsing/parsing_map_utils.c \
				srcs/ray_casting/ray_cast.c \
				srcs/ray_casting/ray_cast_utils.c \
				srcs/ray_casting/sprites_cast.c \
				srcs/ray_casting/draw_walls.c \
				srcs/key_hook.c \
				srcs/fct_loop_hook.c \
				srcs/main.c \
				srcs/errors.c \
				srcs/bmp_creator.c

OBJS		= ${SRCS:.c=.o}

RM			= rm -f

LIBFT		= libft

NAME_LIBFT	= libft.a

NAME		= cub3d

CC			= gcc

CFLAGS		= -Wall -Wextra -Werror

FLAGS		= -framework OpenGL -framework AppKit -lmlx

all:		${NAME}

${NAME}:	${OBJS}
			make -C $(LIBFT)
			cp ${LIBFT}/${NAME_LIBFT} .
			${CC} ${CFLAGS} -o ${NAME} ${FLAGS} ${OBJS} ${NAME_LIBFT}

clean:		
			make -C $(LIBFT) clean
			${RM} ${OBJS}

fclean:		clean
			cd ${LIBFT} && ${RM} ${NAME_LIBFT}
			${RM} ${NAME} ${NAME_LIBFT}

re:			fclean all

.PHONY:		all clean fclean re
