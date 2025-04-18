# Executables
NAME = minishell

# Compilation
CC = cc
COMPL_FLAGS = -Wall -Wextra -Werror
LINK_FLAGS = -lreadline -I/home/kali/.brew/opt/readline/include -L/home/kali/.brew/opt/readline/lib
# -g3 -fsanitize=address

COMPILE = $(CC) $(COMPL_FLAGS)
LINK = $(CC) $(LINK_FLAGS)

# Directories
EXEC = executer
PARS = parser
OBJ_DIR = obj

# Sub-Directories (executer)
PROT = $(EXEC)/protection
HLP = $(EXEC)/helpers
PTH = $(EXEC)/get_path
BLT_IN = $(EXEC)/built-ins
BLT_IN_UTL = $(BLT_IN)/utils

# Sub-Directories (parser)
XPND = $(PARS)/expanding
HEREDOC = $(PARS)/here_doc
UTL = $(PARS)/parsing_utils
TKN = $(PARS)/tokens

# obj dirs
OBJ_DIRS = $(OBJ_DIR)/$(PROT) $(OBJ_DIR)/$(HLP) $(OBJ_DIR)/$(PTH) $(OBJ_DIR)/$(BLT_IN) $(OBJ_DIR)/$(BLT_IN_UTL) \
		   $(OBJ_DIR)/$(XPND) $(OBJ_DIR)/$(HEREDOC) $(OBJ_DIR)/$(UTL) $(OBJ_DIR)/$(TKN) \
		   $(OBJ_DIR)/garbage $(OBJ_DIR)/utils $(OBJ_DIR)/utils/env_utils

# INC
INC = minishell.h structs.h $(PARS)/parser.h $(EXEC)/executer.h $(EXEC)/exec_structs.h utils/utils.h

# General utils
UTILS_FILES = \
	count_words.c ft_getenv.c ft_isprint.c ft_memchr.c ft_putchar_fd.c ft_strchr.c ft_strlcat.c ft_strrchr.c \
	env_utils/env1.c env_utils/env2.c ft_isalnum.c ft_itoa.c ft_memcmp.c ft_putendl_fd.c ft_strcmp.c ft_strlcpy.c ft_tolower.c \
	exit_status.c ft_isalpha.c ft_lstadd_front_bonus.c ft_memcpy.c ft_putnbr_fd.c ft_strdup.c ft_strlen.c ft_toupper.c \
	ft_atoi.c ft_isascii.c ft_lstlast_bonus.c ft_memmove.c ft_putstr_fd.c ft_striteri.c ft_strncmp.c \
	ft_bzero.c ft_isdigit.c ft_lstsize_bonus.c ft_memset.c ft_split.c ft_strjoin.c ft_strnstr.c
GENERAL_UTILS = $(addprefix utils/, $(UTILS_FILES))

# SRC
SRC = main.c main_utils.c \
		$(EXEC)/execute.c \
		$(PROT)/ft_dup2.c $(PROT)/ft_fork.c $(PROT)/ft_open.c $(PROT)/ft_pipe.c \
		$(HLP)/clear_all.c $(HLP)/close_useless_pipes.c $(HLP)/exec_builtin.c $(HLP)/execute_task_by_idx.c $(HLP)/fork_and_pipe.c $(HLP)/wait_children.c \
		$(PTH)/get_path.c $(PTH)/path_utils.c \
		$(BLT_IN)/cd.c $(BLT_IN)/echo.c $(BLT_IN)/export.c $(BLT_IN)/exit.c $(BLT_IN)/env.c $(BLT_IN)/unset.c $(BLT_IN)/pwd.c \
		$(BLT_IN_UTL)/export_utils.c \
		$(PARS)/minishell.c $(PARS)/signals.c $(PARS)/syntax_error.c \
		$(XPND)/expanding.c $(XPND)/env_expand.c \
		$(HEREDOC)/here_doc.c $(HEREDOC)/here_doc_utils.c \
		$(UTL)/analyse_tools.c $(UTL)/ft_strtok.c $(UTL)/utils.c $(UTL)/utils_1.c $(UTL)/utils_2.c $(UTL)/utils_3.c $(UTL)/utils_4.c \
		$(TKN)/analyse.c $(TKN)/ft_create_tokens.c $(TKN)/quote_removal.c \
		garbage/ft_malloc.c garbage/utils.c \
		$(GENERAL_UTILS)

# OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(LINK) $(OBJ) -o $@
	@echo "[CREATING $@...]"

$(OBJ_DIRS):
	@mkdir -p $(OBJ_DIRS)
	@echo "[CREATING object directories...]"

$(OBJ_DIR)/%.o: %.c $(INC) | $(OBJ_DIRS)
	@$(COMPILE) -c $< -o $@
	@echo "[COMPILING $<...]"

clean:
	@rm -rf $(OBJ_DIR)
	@echo "[CLEANING object files...]"

fclean: clean
	@rm -f $(NAME)
	@echo "[CLEANING the executable...]"

re: fclean all
