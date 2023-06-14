#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _ 
# ___ __|  __/   |   |  (   |    <    __/ 
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		:= minishell
CC			:= gcc
FLAGS		:= #-Wall -Wextra -Werror 
FSAN		:= -fsanitize=address
# LDFLAGS		= -L/goinfre/tzi-qi/.brew/opt/readline/lib
# CPPFLAGS	= -I/goinfre/tzi-qi/.brew/opt/readline/include

################################################################################
#                               PROGRAM'S INCLUDES                             #
################################################################################

LIBFT_DIR = libft/
LIBFT = libft.a

LIB := -lft -L./$(LIBFT_DIR)
READLINE = -lreadline

INC_DIR		= includes
INC			= -I./$(INC_DIR)
INC_LIBFT	= -I./$(LIBFT_DIR)$(INC_DIR)

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRC_DIR		:= ./src
SRC			:= $(addsuffix .c, \
					main\
					builtin\
					env\
					execute\
					history\
					lexer\
					parser\
					path\
					pipe\
					prompt\
					quote\
					redirect\
					signal\
					ft_utlis)

OBJ_DIR		:= ./obj
OBJ			:= $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@ $(CC) $(FLAGS) $(FSAN) $(INC) $(INC_LIBFT) -c $< -o $@
	@ printf "$(YELLOW)$<$(CLR_RMV)... "

################################################################################
#                                  Makefile  objs                              #
################################################################################


CLR_RMV		:= \033[0m
RED		    := \033[1;31m
GREEN		:= \033[1;32m
YELLOW		:= \033[1;33m
BLUE		:= \033[1;34m
CYAN 		:= \033[1;36m
RM			:= rm -f

$(NAME): $(LIBFT) $(OBJ) 
	@ echo "\n$(GREEN)Compilation $(CLR_RMV)of $(BLUE)$(NAME) $(CLR_RMV)..."
	@ $(CC) $(FLAGS) $(FSAN) $(LIB) $(READLINE) $(OBJ) -o $(NAME)  
	@ echo "$(GREEN)[Success] $(BLUE)$(NAME) $(CLR_RMV)created ✔️"

$(LIBFT):
	@ echo "$(GREEN)Making $(CYAN)Libft $(CLR_RMV) library..."
	@ $(MAKE) -C $(LIBFT_DIR)
	@ echo "$(GREEN)Generating $(BLUE)minishell $(CLR_RMV)object files..."

all: $(NAME)

bonus: all

run:
	@ ./$(NAME)

clean:
	@ $(RM) *.o */*.o */*/*.o 
	@ $(RM) -r $(OBJ_DIR)
	@ echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)objs ✔️"

fclean: clean
	@ $(RM) $(NAME)
	@ $(MAKE) fclean -C $(LIBFT_DIR)
	@ echo "$(RED)Deleting $(BLUE)$(NAME) $(CLR_RMV)binary ✔️"

re:			fclean all

.PHONY:		all clean fclean re
