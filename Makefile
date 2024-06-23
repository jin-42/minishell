# ------------- VARIABLES ------------- #

NAME = minishell

CC = cc
CFLAGS = -Wall -Wextra -Werror -g3
LIBS = -lreadline

LIBRARY = full_libft/libft.a

HEADER = includes/minishell.h

SRC_DIR = sources/

SRC = $(SRC_DIR)main.c \
	$(SRC_DIR)signals.c \
	$(SRC_DIR)free.c \
	$(SRC_DIR)error.c \
	$(SRC_DIR)env_parsing.c \
	$(SRC_DIR)env_manip.c \
	$(SRC_DIR)exec.c \
	$(SRC_DIR)exec_paths.c \
	$(SRC_DIR)exec_pipes.c \
	$(SRC_DIR)builtin.c \
	$(SRC_DIR)builtin_env.c \
	$(SRC_DIR)builtin_pwd.c \
	$(SRC_DIR)builtin_cd.c \
	$(SRC_DIR)builtin_unset.c \
	$(SRC_DIR)builtin_export.c \
	$(SRC_DIR)builtin_export_utils.c \
	$(SRC_DIR)builtin_echo.c \
	$(SRC_DIR)builtin_exit.c \
	$(SRC_DIR)lexer_join.c \
	$(SRC_DIR)lexer_quote.c \
	$(SRC_DIR)lexer_redir.c \
	$(SRC_DIR)lexer.c \
	$(SRC_DIR)close_quotes.c \
	$(SRC_DIR)parser.c \
	$(SRC_DIR)parser_utils.c \
	$(SRC_DIR)parser_expand.c \
	$(SRC_DIR)parser_heredoc.c \
	$(SRC_DIR)exec_files.c \
	$(SRC_DIR)backslash.c \
	$(SRC_DIR)parser_redir.c \
	$(SRC_DIR)env_utils.c \
	$(SRC_DIR)split_token.c \
	$(SRC_DIR)error_heredoc.c \
	$(SRC_DIR)split_token_utils.c

OBJ_DIR = ./OBJ/

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)

# --------------- RULES --------------- #

all: lib
	$(MAKE) $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) done$(END)"

lib:
	$(MAKE) -C full_libft/
	@echo "$(BOLD)$(GREEN)$(LIBRARY) done$(END)"

clean:
	rm -rf $(OBJ_DIR)
	$(MAKE) -C full_libft/ clean
	@echo "$(BOLD)$(RED)clean done$(END)"

fclean: clean
	rm -rf $(NAME)
	$(MAKE) -C full_libft/ fclean
	@echo "$(BOLD)$(RED)fclean done$(END)"

re: fclean all

.PHONY: clean fclean re all lib

# ------------ COMPILATION ------------- #

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBRARY) $(LIBS)

$(OBJ_DIR)%.o: %.c $(HEADER) $(LIBRARY)
	@mkdir -p $(OBJ_DIR)$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< 

