# due to problems we had with bash, now we are using a makefile in order to organize our compilation stuff

# Executables
NAME=minishell

# Compilation
COMPILE = cc -Wall -Wextra -Werror

# Directories
EXEC=/executer
PARS=/parser
OBJ_DIR=obj

# INC
INC = 

# SRC
SRC = main.c

# OBJ
OBJ = $(addprefix $(OBJ_DIR)/, $(SRC:.c=.o))

# Rules
all: $(NAME)

$(NAME): $(OBJ)
#	@$(COMPILE) $(OBJ) -o $@
	@echo [CREATING $@ ... ]

$(OBJ_DIR): 
	@mkdir $(OBJ_DIR)
	@echo [CREATING $(OBJ_DIR) ... ]

$(OBJ_DIR)/%.o: %.c $(INC) | $(OBJ_DIR)
	@$(COMPILE) $< -c $@
	@echo [COMPILING $< ... ]

clean:
	@rm -fr $(OBJ_DIR)
	@echo [CLEANING ... ]

fclean: clean
	@rm -fr $(NAME)
	@echo [CLEANING ... ]

re: fclean all
