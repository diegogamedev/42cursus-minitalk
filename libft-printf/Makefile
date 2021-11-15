# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dienasci <dienasci@student.42sp.org.br >   +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/09/07 12:29:34 by dienasci          #+#    #+#              #
#    Updated: 2021/09/14 19:42:16 by dienasci         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = libftprintf.a

CC = clang

LIBFT = libft.a

LIBFT_PATH = ./libft/

SRCS =	src/ft_printf.c src/ft_printf_aux.c

CFLAGS = -Wall -Werror -Wextra

OBJS = ${SRCS:.c=.o}

RM = rm -f

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT_PATH)
		$(CC) $(CFLAGS) -c $(SRCS)
		make -C $(LIBFT_PATH) $(LIBFT)
		cp $(LIBFT_PATH)/$(LIBFT) .
		mv $(LIBFT) $(NAME)
		ar -rcs $(NAME) $(OBJS)

clean:
		$(RM) $(OBJS)
		$(RM) $(OBJS:src/%=%)
		make -C $(LIBFT_PATH) clean

fclean: clean
		$(RM) $(NAME)
		$(RM) $(LIBFT_PATH)$(LIBFT)

re: fclean all

debug:
		CFLAGS += -g3
		all

.PHONY: debug re fclean all
