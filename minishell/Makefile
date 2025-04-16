NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): minishell.c utils.c $(LIBFT)
	@gcc -Wall -Wextra -I./libft $^ -L./libft -lft -lreadline -o $@
	echo "compilation reussie !"

$(LIBFT):
	@make -C ./libft

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re