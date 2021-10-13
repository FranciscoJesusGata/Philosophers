# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 19:57:08 by fgata-va          #+#    #+#              #
#    Updated: 2021/10/04 14:00:51 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

CFLAGS = -Wall -Werror -Wextra -I. -g

NAME = philo

SRC = philo.c

OBJS = ${SRC:.c=.o}

$(NAME): $(OBJS)
	gcc -Wall -Werror -Wextra -I. $(OBJS) -o $(NAME)

norm:
	norminette $(SRC) *.h

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all
