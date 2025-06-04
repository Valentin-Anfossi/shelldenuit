NAME = minishell
LIBFT = ./libft/libft.a
SRCS = \
 	srcs/utils.c			\
 	srcs/tokens.c 			\
 	srcs/tokens_utils.c 	\
 	srcs/tokens_utils2.c	\
	srcs/expand.c			\
	srcs/redir.c 			\
 	srcs/jobs.c 			\
 	srcs/jobs_utils.c 		\
 	srcs/commands.c 		\
	srcs/status.c			\
	srcs/errors.c 			\
	srcs/builtins/cd.c		\
	srcs/builtins/echo.c	\
	srcs/builtins/env.c 	\
	srcs/builtins/exit.c	\
 	srcs/builtins/export.c	\
	srcs/builtins/unset.c	\
	srcs/ms_execvp.c		\
	srcs/execute.c			\
	srcs/execute_utils.c	\
 	srcs/signals.c			\
 	srcs/minishell.c

BUILD_DIR = build/Debug
OUT_DEBUG = $(BUILD_DIR)/outDebug

all: $(NAME)

$(NAME): $(SRCS) $(LIBFT)
	@gcc -g -Wall -Wextra -I./libft $^ -L./libft -lft -lreadline -o $@
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

