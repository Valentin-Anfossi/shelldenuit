NAME = minishell
LIBFT = ./libft/libft.a
SRCS = \
 	srcs/utils.c		\
 	srcs/tokens.c 		\
 	srcs/tokens_utils.c \
 	srcs/tokens_utils2.c 	\
	srcs/expand.c		\
 	srcs/jobs.c 		\
 	srcs/jobs_utils.c 	\
 	srcs/commands.c 	\
 	srcs/export.c 	\
 	srcs/minishell.c \
	srcs/errors.c \
	srcs/unset.c \
	srcs/echo.c \
	srcs/expand.c \
	srcs/env.c \
	srcs/cd.c \
	srcs/exit.c \
	srcs/execute.c \
	srcs/ms_execvp.c

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

