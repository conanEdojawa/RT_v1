# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 16:14:13 by yoelguer          #+#    #+#              #
#    Updated: 2020/12/20 19:55:57 by yzemmour         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= 	main.c \
			plane.c\
			ray.c\
			rt.c\
			sphere.c\
			vector.c\
			file.c\

OBJ = $(addprefix $(OBJ_DIR)/,$(SRC:.c=.o))

NAME 	= RTv1

CFLAGS = -Wall -Wextra -Werror

INCLUDE	= -I /Users/yzemmour/.brew/Cellar/sdl2/2.0.12_1/include 

LIB = -L /Users/yzemmour/.brew/Cellar/sdl2/2.0.12_1/lib 

SDL = -l SDL2-2.0.0

SRC_DIR = ./src

OBJ_DIR = ./obj

LIBFT_DIR = ./libft

LIBFT_LIB = $(LIBFT_DIR)/libft.a


CC = @gcc

all : $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_DIR)

$(NAME) : $(LIBFT_LIB) $(OBJ)
	@gcc $(OBJ) $(CFLAGS) -o $(NAME) $(INCLUDE) $(LIB)  $(SDL) $(LIBFT_LIB)
	@echo "\033[92mDone for RTV1\033[0m"

$(OBJ_DIR):
	@-mkdir $(OBJ_DIR)

$(OBJ): $(OBJ_DIR)/%.o : $(SRC_DIR)/%.c $(HEADER) | $(OBJ_DIR)
	@gcc -c  $(INCLUDE) $< -o $@ 

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ_DIR)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

norme:
	@norminette $(SRC_DIR)

re : fclean all
