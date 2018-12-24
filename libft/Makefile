# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: agrodzin <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/19 20:54:26 by agrodzin          #+#    #+#              #
#    Updated: 2018/11/23 11:17:19 by agrodzin         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC=gcc
CFLAGS=-I -Wall -Werror -Wextra -c
SRCS=ft_strtoupper.c\
 	ft_memset.c\
	 ft_bzero.c\
	 ft_memcpy.c\
	 ft_memccpy.c\
	 ft_memmove.c\
	 ft_memchr.c\
	 ft_memcmp.c\
	 ft_strlen.c\
	 ft_strdup.c\
	 ft_strcpy.c\
	 ft_strncpy.c\
	 ft_strcat.c\
	 ft_strncat.c\
	 ft_strlcat.c\
	 ft_strchr.c\
	 ft_strrchr.c\
	 ft_strstr.c\
	 ft_strnstr.c\
	 ft_strcmp.c\
	 ft_strncmp.c\
	 ft_atoi.c\
	 ft_isalpha.c\
	 ft_isdigit.c\
	 ft_isalnum.c\
	 ft_isascii.c\
	 ft_isprint.c\
	 ft_toupper.c\
	 ft_tolower.c\
	 ft_memalloc.c\
	 ft_memdel.c\
	 ft_strnew.c\
	 ft_strdel.c\
	 ft_strclr.c\
	 ft_striter.c\
	 ft_striteri.c\
	 ft_strmap.c\
	 ft_strmapi.c\
	 ft_strequ.c\
	 ft_strnequ.c\
	 ft_strsub.c\
	 ft_strjoin.c\
	 ft_strtrim.c\
	 ft_strsplit.c\
	 ft_itoa_base.c\
	 ft_putchar.c\
	 ft_putstr.c\
	 ft_putendl.c\
	 ft_putnbr.c\
	 ft_putchar_fd.c\
	 ft_putstr_fd.c\
	 ft_putendl_fd.c\
	 ft_putnbr_fd.c\
	 ft_lstnew.c\
	 ft_lstdelone.c\
	 ft_lstdel.c\
	 ft_lstadd.c\
	 ft_lstiter.c\
	 ft_lstmap.c\
	 ft_realloc.c\
	 clear_2d.c\
	 print_args.c\
	 reset_int_arr.c\
	 how_many.c\
	 free_two_d.c\
	 how_many_2d.c\
	 ft_is_space_tab.c\
	 free_two.c\
	 get_num_int_arr.c\
	 is_ws.c
NAME=libft.a
LIB=ar rs
OBJ=$(SRCS:%.c=%.o)

all: $(NAME)

$(NAME): $(OBJ)
	$(LIB) $(NAME) $(OBJ)

$(OBJ): $(SRCS)
	$(CC) $(CFLAGS) $(SRCS)

clean:
	/bin/rm -f *.o

fclean:
	/bin/rm -f *.a *.o
	
re: fclean all
