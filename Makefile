# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fgata-va <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/20 19:57:08 by fgata-va          #+#    #+#              #
#    Updated: 2021/12/07 17:37:42 by fgata-va         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC := gcc

SRCDIR := src
OBJDIR := build
INCLUDE_DIR := includes

CFLAGS := -Wall -Werror -Wextra -I$(INCLUDE_DIR)/ -g

NAME := philo

SRC := $(addprefix $(SRCDIR)/, philo.c philo_utils_1.c)

OBJS := $(patsubst $(SRCDIR)/%,$(OBJDIR)/%,$(SRC:.c=.o))

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

$(OBJDIR):
	mkdir $@

$(OBJDIR)/%.o: $(SRCDIR)/%.c | $(OBJDIR)
	$(CC) $(CFLAGS)   -c -o $@ $<

echo:
	echo $(SRC)
	echo $(OBJS)

norm:
	norminette $(SRC) *.h

all: $(NAME)

clean:
	rm -rf $(OBJS)

fclean: clean
	rm -rf $(NAME) $(NAME).dSYM

re: fclean all
