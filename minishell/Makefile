NAME = minishell
LIBFT = ./libft/libft.a

all: $(NAME)

$(NAME): srcs/minishell.c srcs/utils.c srcs/jobs.c srcs/tokens.c srcs/tokens_utils.c srcs/jobs_utils.c $(LIBFT)
	@gcc -g -Wall -Wextra -I./libft $^ -L./libft -lft -lreadline -o $@
	echo "compilation reussie !"

$(LIBFT):
	@make -C ./libft

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re