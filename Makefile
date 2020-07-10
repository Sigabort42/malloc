#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: elbenkri <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2017/11/08 17:04:50 by elbenkri          #+#    #+#              #
#    Updated: 2018/01/31 13:59:01 by elbenkri         ###   ########.fr        #
#                                                                              #
#******************************************************************************#

ifeq ($(HOSTTYPE),)
	HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME			=	libft_malloc$(HOSTTYPE).so

LINK_NAME		=	libft_malloc.so

CC			=	gcc

LIBFT			= 	-L./libft/ -lft

CFLAGS			=	-Wall -Wextra -Werror

PATH_SRCS		=	srcs/

SRCS			=	$(PATH_SRCS)malloc.c \
				$(PATH_SRCS)find.c \
				$(PATH_SRCS)free.c \
				$(PATH_SRCS)realloc.c \
				$(PATH_SRCS)show_alloc_mem.c \


OBJ			=	$(SRCS:.c=.o)

HEADER			=	libft.h

all: $(NAME)

$(NAME): $(OBJ)
	@make -C libft/
	@$(CC) -I ./libft $(LIBFT) -shared $(SRCS) -o $(NAME)
	@echo "\033[H\033[2J\033[32;5m[OK...]"
	ln -s $(NAME) $(LINK_NAME)

clean:
	@make -C libft/ clean
	@rm -rf $(OBJ)
	@echo "\033[H\033[2J\033[32;5m[OK...]"

fclean:	clean
	@make -C libft/ fclean
	@rm -rf $(NAME) $(LINK_NAME)
	@echo "\033[H\033[2J\033[32;5m[OK...]"

re: fclean all
