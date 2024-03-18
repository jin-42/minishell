# ------------- VARIABLES ------------- #

NAME = minishell
#NAME_BON = minishell_bonus

CC = cc
CFLAGS = -g3
LIBS = -lreadline -lncurses

LIBRARY = full_libft/libft.a

HEADER = includes/minishell.h
#HEADER_BON = $(SRC_BON_DIR)minishell.h

SRC_DIR = sources/
#SRC_BON_DIR = bonus/

SRC = $(SRC_DIR)main.c

#SRC_BON = 

OBJ_DIR = ./OBJ/
#OBJ_BON_DIR = ./OBJ_BON/

OBJ = $(SRC:%.c=$(OBJ_DIR)%.o)
#OBJ_BON = $(SRC_BON:%.c=$(OBJ_BON_DIR)%.o)

# --------------- RULES --------------- #

all: lib
	$(MAKE) $(NAME)
	@echo "$(BOLD)$(GREEN)$(NAME) done$(END)"

#bonus: lib
#	$(MAKE) $(NAME_BON)
#	@echo "$(BOLD)$(GREEN)$(NAME_BON) done$(END)"

lib:
	$(MAKE) -C full_libft/
	@echo "$(BOLD)$(GREEN)$(LIBRARY) done$(END)"

clean:
	rm -rf $(OBJ_DIR)
#	rm -rf $(OBJ_BON_DIR)
	$(MAKE) -C full_libft/ clean
	@echo "$(BOLD)$(RED)clean done$(END)"

fclean: clean
	rm -rf $(NAME)
#	rm -rf $(NAME_BON)
	$(MAKE) -C full_libft/ fclean
	@echo "$(BOLD)$(RED)fclean done$(END)"

re: fclean all

.PHONY: clean fclean re all lib# bonus

# ------------ COMPILATION ------------- #

$(NAME): $(OBJ) $(LIBRARY)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(LIBRARY) $(LIBS)

#$(NAME_BON): $(OBJ_BON) $(LIBRARY)
#	$(CC) $(CFLAGS) -o $@ $(OBJ_BON) $(LIBRARY)

$(OBJ_DIR)%.o: %.c $(HEADER) $(LIBRARY)
	@mkdir -p $(OBJ_DIR)$(SRC_DIR)
	$(CC) $(CFLAGS) -o $@ -c $< $(LIBS)

#$(OBJ_BON_DIR)%.o: %.c $(HEADER_BON) $(LIBRARY)
#	@mkdir -p $(OBJ_BON_DIR)$(SRC_BON_DIR)
#	$(CC) $(CFLAGS) -c -o $@ $<

# -------------- COLORS ---------------- #

ERASE	=	\033[2K\r
GREY	=	\033[30m
RED		=	\033[31m
GREEN	=	\033[32m
YELLOW	=	\033[33m
BLUE	=	\033[34m
PINK	=	\033[35m
CYAN	=	\033[36m
WHITE	=	\033[37m
BOLD	=	\033[1m
UNDER	=	\033[4m
SUR		=	\033[7m
END		=	\033[0m