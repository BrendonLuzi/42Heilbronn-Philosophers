# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: bluzi <bluzi@student.42.fr>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/02/10 16:44:25 by bluzi             #+#    #+#              #
#    Updated: 2023/06/29 07:13:33 by bluzi            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		:= philo

CFLAGS		:= -pthread #-fsanitize=thread -g

SRCS		:= 	src/control.c	\
				src/main.c		\
				src/init.c		\
				src/parsing.c	\
				src/routine.c	\
				src/time.c		\
				src/utils.c		\
			
OBJS		:= ${SRCS:.c=.o}

all: $(NAME)

%.o: %.c
	@$(CC) $(CFLAGS) -o $@ -c $<

$(NAME): $(OBJS)
	@$(CC) $(OBJS) $(CFLAGS) -o $(NAME)
	@make clean

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all, clean, fclean, re