# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mhotting <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/14 11:49:03 by mhotting          #+#    #+#              #
#    Updated: 2023/11/25 10:04:35 by mhotting         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	=	prog
CC		=	cc
ifndef NO_FLAGS
	CFLAGS	=	-Wall -Werror -Wextra
else
	CFLAGS	=	-w
endif
HEADERS	=	get_next_line.h
SRCS	=	main.c					\
			get_next_line.c			\
			get_next_line_utils.c
OBJS	=	$(SRCS:.c=.o)
ifndef BUFFER_SIZE
	BUFFER_SIZE	=	1000
endif


all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $(NAME)

%.o: %.c $(HEADERS)
	$(CC) $(CFLAGS) -c $< -o $@ -I. -D BUFFER_SIZE=$(BUFFER_SIZE)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
