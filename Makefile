# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: falatrac <falatrac@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/10/13 17:32:59 by ktombola          #+#    #+#              #
#    Updated: 2025/11/14 18:26:34 by falatrac         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME    := miniRT

CC      := cc
CFLAGS  := -Wall -Wextra -Werror
INCLUDES := -Iincludes -Ilibft -Imlx

LIBFT   := libft/libft.a
MLX     := mlx/libmlx.a
MLXFLAGS := -Lmlx -lmlx -lXext -lX11 -lm

#--------------------------- MANDATORY PART ---------------------------#

SRC_MAND  := src/main.c src/errors.c \
             src/parse/parsing.c src/parse/scene.c \
             src/parse/objects.c src/parse/utils.c src/parse/utils1.c \
             src/parse/conversions.c \
             src/render/mlbx.c src/ray.c \
             src/intersections/closest.c src/intersections/utils.c \
             src/math/utils.c src/math/utils2.c \
             src/render/color.c src/render/color_cal.c \
             src/render/light.c

OBJ_MAND  := $(SRC_MAND:.c=.o)

#----------------------------- BONUS PART -----------------------------#

SRC_BONUS := src/main.c src/errors.c \
             src/parse/parsing.c src/parse/scene.c \
             src/parse/objects.c src/parse/utils.c src/parse/utils1.c \
             src/parse/conversions.c \
             src/render/mlbx.c src/ray.c \
             src/intersections/closest.c src/intersections/utils.c \
             src/math/utils.c src/math/utils2.c \
             src/render/color.c src/render/color_cal.c \
             src/render/light_bonus.c

OBJ_BONUS := $(SRC_BONUS:.c=.o)

#---------------------------- DEFAULT RULE ----------------------------#


all: $(NAME)

$(NAME): $(OBJ_MAND) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_MAND) -Llibft -lft $(MLXFLAGS) -o $(NAME)

#--------------------------- COMPILATION RULE -------------------------#


%.o: %.c
	$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

#---------------------------- LIBS BUILD ------------------------------#


$(LIBFT):
	make -C libft

$(MLX):
	make -C mlx
	
#------------------------------ BONUS --------------------------------#


bonus: $(OBJ_BONUS) $(LIBFT) $(MLX)
	$(CC) $(CFLAGS) $(OBJ_BONUS) -Llibft -lft $(MLXFLAGS) -o $(NAME)


#------------------------------ CLEAN --------------------------------#

clean:
	rm -f $(OBJ_MAND) $(OBJ_BONUS)
	make clean -C libft
	make clean -C mlx

fclean: clean
	rm -f $(NAME)
	make fclean -C libft

re: fclean all

.PHONY: all clean fclean re bonus

#------------------------------- END ---------------------------------#
