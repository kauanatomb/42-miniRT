# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ktombola <ktombola@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 17:32:59 by ktombola          #+#    #+#              #
#    Updated: 2025/10/13 17:50:29 by ktombola         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := miniRT

SRC     := src/main.c src/errors.c src/parse/parsing.c src/parse/scene.c \
		src/parse/utils.c src/parse/utils1.c src/parse/conversions.c \
		src/parse/objects.c src/mlbx.c src/ray.c src/intersections/closest.c \
		src/math/utils.c src/math/utils2.c src/color.c\

OBJ     := $(SRC:.c=.o)

CC      := cc
CFLAGS  := -Wall -Wextra -Werror

INCLUDES := -Iincludes -Ilibft -Imlx

LIBFT   := libft/libft.a
MLX     := mlx/libmlx.a
MLXFLAGS := -Lmlx -lmlx -lXext -lX11 -lm

all: $(NAME)

$(NAME): $(OBJ) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ) -Llibft -lft $(MLXFLAGS) -o $(NAME)

%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx

clean:
	rm -f $(OBJ)
	make clean -C libft
	make clean -C mlx

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re