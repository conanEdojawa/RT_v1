# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: yoelguer <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/22 16:14:13 by yoelguer          #+#    #+#              #
#    Updated: 2020/02/22 15:55:05 by yoelguer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRC		= 	main.c \
			vector.c \

OBJ		= $(SRC:.c=.o)

NAME 	= RTv1

CFLAGS = -Wall -Wextra -Werror

FLAG	= -I include -L lib -l SDL2-2.0.0

CC = @gcc

all : $(NAME)

$(NAME) : 
	@make -C ./libft/
	@gcc $(SRC) $(CFLAGS) -o $(NAME) $(FLAG)  libft/libft.a
	@echo "\033[92mDone for RTV1\033[0m"

clean :
	@make clean -C ./libft/
	@rm -rf $(OBJ)

fclean : clean
	@make fclean -C ./libft/
	@rm -rf $(NAME)

norme:
	@norminette $(SRC)

re : fclean all
