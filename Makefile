# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ele-borg <ele-borg@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/09/04 18:23:01 by ele-borg          #+#    #+#              #
#    Updated: 2025/06/03 16:23:08 by ele-borg         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#variables

SRC_DIR = sources
OBJ_DIR = objets
GC_DIR = gc

SRC_FILES = ${SRC_DIR}/main.c \
			${GC_DIR}/gc_cleanup.c \
			${GC_DIR}/gc_malloc.c \
			${GC_DIR}/gc_realloc.c \
			${GC_DIR}/gc_remove.c \
			${SRC_DIR}/get_next_line.c \
			${SRC_DIR}/get_next_line_utils.c \
			${SRC_DIR}/utils.c \
			${SRC_DIR}/parsing.c \
			${SRC_DIR}/parsing_get_texture.c \
			${SRC_DIR}/parsing_check_texture.c \
			${SRC_DIR}/parsing_check_color.c \
			${SRC_DIR}/parsing_extention.c \
			${SRC_DIR}/parsing_get_map.c \
			${SRC_DIR}/parsing_flood_fill.c \

OBJ_FILES =	$(OBJ_DIR)/main.o \
			${OBJ_DIR}/gc_cleanup.o \
			${OBJ_DIR}/gc_malloc.o \
			${OBJ_DIR}/gc_realloc.o \
			${OBJ_DIR}/gc_remove.o \
			$(OBJ_DIR)/get_next_line.o \
			$(OBJ_DIR)/get_next_line_utils.o \
			$(OBJ_DIR)/utils.o \
			$(OBJ_DIR)/parsing.o \
			$(OBJ_DIR)/parsing_get_texture.o \
			$(OBJ_DIR)/parsing_check_texture.o \
			$(OBJ_DIR)/parsing_check_color.o \
			$(OBJ_DIR)/parsing_extention.o \
			$(OBJ_DIR)/parsing_get_map.o \
			$(OBJ_DIR)/parsing_flood_fill.o \


NAME = cub3D

FLAGS_C = -Wall -Wextra -g3 -I.
# FLAGS_C = -Wall -Wextra -Werror -g3 -I.

CC = cc

#rules

all: ${NAME}

${NAME}: ${OBJ_FILES}
	${CC} ${OBJ_FILES} -o ${NAME}

${OBJ_DIR}/%.o: ${SRC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	$(CC) -c $(FLAGS_C) $< -o $@

${OBJ_DIR}/%.o: ${GC_DIR}/%.c
	@mkdir -p ${OBJ_DIR}
	$(CC) -c $(FLAGS_C) $< -o $@

GC_OBJ_FILES:
	$(MAKE) -C ${GC_DIR}

clean:
	rm  -f ${OBJ_FILES}

fclean: clean
	rm -f ${NAME}

re: fclean all

reclean : all clean

.PHONY: all clean fclean re
