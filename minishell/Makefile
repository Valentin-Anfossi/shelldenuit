NAME = minishell
LIBFT = ./libft/libft.a
SRCS = srcs/commands/commands.c	\
srcs/commands/builtins/cd.c \
srcs/commands/builtins/echo.c \
srcs/commands/builtins/env.c \
srcs/commands/builtins/exit.c \
srcs/commands/builtins/export.c \
srcs/commands/builtins/export2.c \
srcs/commands/builtins/pwd.c \
srcs/commands/builtins/unset.c \
srcs/debug/debug_print_tokens.c \
srcs/execute/execute_fileredirs.c \
srcs/execute/execute_pipes.c \
srcs/execute/execute_redirerror.c \
srcs/execute/execute_redirs.c \
srcs/execute/execute_single.c \
srcs/execute/execute_utils.c \
srcs/execute/execute.c \
srcs/execute/jobs_utils.c \
srcs/execute/jobs.c \
srcs/execute/jobs2.c \
srcs/execute/ms_execvp.c \
srcs/execute/ms_execvp2.c \
srcs/tokens/tokens_add.c \
srcs/tokens/tokens_check.c \
srcs/tokens/tokens_concat.c \
srcs/tokens/tokens_env.c \
srcs/tokens/tokens_env2.c \
srcs/tokens/tokens_free.c \
srcs/tokens/tokens_lst.c \
srcs/tokens/tokens_lst2.c \
srcs/tokens/tokens_split.c \
srcs/tokens/tokens_types.c \
srcs/tokens/tokens_utils.c \
srcs/tokens/tokens_utils2.c \
srcs/tokens/tokens_utils3.c \
srcs/utils/errors.c \
srcs/utils/free.c \
srcs/utils/init.c \
srcs/utils/signals.c \
srcs/utils/status.c \
srcs/utils/utils.c \
srcs/utils/utils2.c \
srcs/utils/utils3.c \
srcs/minishell.c

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

