NAME = minishell
LIBFT = ./libft/libft.a
SRCS = srcs/commands/*.c	\
srcs/execute/*.c			\
srcs/*.c \
srcs/utils/*.c				\
srcs/tokens/*.c \
srcs/commands/builtins/*.c\
srcs/debug/*.c

BUILD_DIR = build/Debug
OUT_DEBUG = $(BUILD_DIR)/outDebug

all: $(NAME)
# -fsanitize=address,undefined,leak
$(NAME): $(SRCS) $(LIBFT)
	@gcc -g -Wall -Wextra -Werror -I./libft $^ -L./libft -lft -lreadline -o $@
	@echo "compilation reussie !"

$(LIBFT):
	@make -C ./libft

debug: $(SRCS) $(LIBFT)
	@mkdir -p ./build
	@mkdir -p $(BUILD_DIR)
	@gcc -g -Wall -Wextra -I./libft $(SRCS) -L./libft -lft -lreadline -o $(OUT_DEBUG)
	@echo "Binaire de debug généré : $(OUT_DEBUG)"

clean:
	@rm -f $(NAME)

fclean: clean
	@make -C ./libft fclean

re: fclean all

.PHONY: all clean fclean re

