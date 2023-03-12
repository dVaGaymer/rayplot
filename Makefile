BIN_DIR		=	bin/
NAME		=	$(BIN_DIR)/rayplot

#----- HEADER -----
H_DIR	=	include
H		=	$(wildcard $(SRC_DIR)/**/*.h)

#----- SRC ----
SRC_DIR		=	src
SRC		=	$(SRC_DIR)/main.c \
			$(wildcard $(SRC_DIR)/**/*.c)

#----- OBJ -----
OBJ_DIR	=	obj
OBJ		=	$(subst $(SRC_DIR),$(OBJ_DIR), $(SRC:.c=.o))

#----- FLAGS -----
CC			=	clang
H_FLAGS		=	-I$(H_DIR)
C_FLAGS		=	-Wall -Wextra -Werror
LIB_FLAGS	=	-lraylib -lm -lpthread -ldl

#----- IMPICIT RULES -----
$(addprefix $(OBJ_DIR)/, %.o): $(addprefix $(SRC_DIR)/, %.c) $(HEAD)
	$(CC) $(H_FLAGS) $(C_FLAGS) -c $< -o $@

#----- RULES
all: $(OBJ_DIR) $(BIN_DIR) $(NAME)

$(OBJ_DIR):
	@cp -a $(SRC_DIR) $(OBJ_DIR)
	@$(RM) $(OBJ:.o=.c)
$(BIN_DIR):
	@mkdir $(BIN_DIR)

$(NAME): $(OBJ) $(H) $(SRC)
	$(CC) $(H_FLAGS) $(LIB_FLAGS) $(OBJ) -o $@

clean:
	$(RM) -rf $(OBJ_DIR)

fclean: clean
	$(RM) -rf $(BIN_DIR)

re: fclean all

n:
	norminette

#----- UTILS -----
RED				=	\033[0;31m
CYAN			=	\033[0;36m
GREEN 			=	\033[1;32m
YELLOW 			=	\033[1;33m
NC 				=	\033[0m

.PHONY: clean fclean re all
