#  |  |  ___ \    \  |         |
#  |  |     ) |  |\/ |   _  |  |  /   _
# ___ __|  __/   |   |  (   |    <    __/
#    _|  _____| _|  _| \__,_| _|\_\ \___|
#                              by jcluzet
################################################################################
#                                     CONFIG                                   #
################################################################################

NAME		:= minishell
# CC			:= clang
CC			:= gcc
FLAGS		:= -Wall -Wextra -Werror
FSAN		:= -fsanitize=address -g3

################################################################################
#                               PROGRAM'S INCLUDES                             #
################################################################################

LIBFT_DIR = libft/
LIBFT = libft.a

LIB := -lft -L./$(LIBFT_DIR)
READLINE = -lreadline -L/usr/local/opt/readline/lib
# READLINE =  -lreadline

INC_DIR		= includes
INC			= -I./$(INC_DIR)
INC_LIBFT	= -I./$(LIBFT_DIR)$(INC_DIR)
INC_RL		= -I/usr/local/opt/readline/include
# INC_RL		= -I/usr/include/readline

################################################################################
#                                 PROGRAM'S SRCS                               #
################################################################################

SRC_DIR		:= ./src
SRC			:= $(addsuffix .c, \
					00_main \
					01_prompt\
					02_expand\
					02a_expand_utils\
					03_lexer\
					03a_lexer_token_count\
					03b_lexer_char_count\
					04_parser\
					04a_parser_utils\
					05_execute\
					05a_exec_utils\
					05b_exec_path\
					06_pipe\
					07_redirection\
					07a_redir_utils\
					07b_redir_heredoc\
					08_builtin\
					08a_echo\
					08b_cd\
					08c_pwd\
					08d_export\
					08e_unset\
					08f_env\
					08g_history\
					08h_exit\
					09_quote\
					09a_quote_utils\
					10_signal\
					11_free\
					12_minishell_utils\
					13_minishell_utils2)

OBJ_DIR		:= ./obj
OBJ			:= $(SRC:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(OBJ_DIR)
	@ $(CC) $(FLAGS) $(FSAN) $(INC) $(INC_LIBFT) $(INC_RL) -c $< -o $@
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
	@ echo "\n$(GREEN)Compilation $(CLR_RMV)of $(BLUE) $(NAME) $(CLR_RMV)..."
	@ $(CC) $(FLAGS) $(FSAN) $(LIB) $(READLINE) $(OBJ) $(LIBFT_DIR)/$(LIBFT) -o $(NAME)
	@ echo "$(GREEN)[Success] $(BLUE)$(NAME) $(CLR_RMV)created ✔️"
	@ ./$(NAME)

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

.PRECIOUS:	$(NAME) $(OBJ)
