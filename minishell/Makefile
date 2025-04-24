NAME = minishell
LIBFT = ./libft/libft.a

SRCS = srcs/*.c

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@gcc -g -Wall -Wextra -I./libft $^ -L./libft -lft -lreadline -o $@
	@echo "compilation reussie !"

$(LIBFT):
	@make -C ./libft

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re