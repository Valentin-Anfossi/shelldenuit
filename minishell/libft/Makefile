# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vanfossi <vanfossi@student.42nice.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/11/07 04:36:42 by vanfossi          #+#    #+#              #
#    Updated: 2025/06/12 15:12:32 by vanfossi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a

SOURCES	= ft_atoi.c ft_bzero.c ft_calloc.c ft_isalnum.c ft_isalpha.c ft_isascii.c \
			ft_isdigit.c ft_isprint.c ft_itoa.c ft_memchr.c ft_memcmp.c ft_memcpy.c \
			ft_memmove.c ft_memset.c ft_putchar_fd.c ft_putendl_fd.c ft_putnbr_fd.c \
			ft_putstr_fd.c ft_split.c ft_strchr.c \
			ft_strdup.c ft_striteri.c ft_strjoin.c ft_strlcat.c ft_strlcpy.c \
			ft_strlen.c ft_strmapi.c ft_strncmp.c ft_strnstr.c ft_strrchr.c \
			ft_strtrim.c ft_substr.c ft_tolower.c ft_toupper.c \
			ft_printf_prints.c ft_printf_prints2.c ft_printf_utils.c \
			ft_printf.c ft_fprintf.c ft_fprintf_prints.c \
			ft_fprintf_prints2.c ft_fprintf_utils.c get_next_line.c \
			ft_isspace.c

BONUSSRCS = ft_lstnew.c ft_lstadd_front.c ft_lstsize.c \
			ft_lstlast.c ft_lstadd_back.c \
			ft_lstdelone.c ft_lstclear.c ft_lstiter.c ft_lstmap.c 

OFILES	= $(SOURCES:.c=.o)

BONUSOFILES = $(BONUSSRCS:.c=.o)

CC	= gcc

FLAGS	= -Wall -Wextra -Werror -I.

all: $(NAME)

$(NAME): $(OFILES)
	@ar rcs $(NAME) $(OFILES)

bonus : $(OFILES) $(BONUSOFILES)
	ar rcs $(NAME) $(OFILES) $(BONUSOFILES)

#Compile .o < .c seulement si changes
%.o: %.c
	@$(CC) $(FLAGS) -c $< -o $@

clean:
	rm -f $(OFILES)
	rm -f $(BONUSOFILES)

fclean: clean
	rm -f $(NAME)

re: fclean all
