# due to problems we had with bash, now we are using a makefile in order to organize our compilation stuff

# Executables
NAME=minishell

# Compilation
COMPILE = cc -Wall -Wextra -Werror

# Directories
EXEC=/executer
PARS=/parser

# INC
INC = 

# SRC
SRC = main.c

# OBJ
OBJ = $(SRC:.c=.o)

# Rules
all: $(NAME)

$(NAME): $(OBJ)
	@$(COMPILE) $(OBJ) -o $@
	@echo [CREATING $@ ... ]

%.o: %.c $(INC)
	@$(COMPILE) $< -c $@
	@echo [COMPILING $< ... ]

clean:
	@rm -fr $(OBJ)
	@echo [CLEANING ... ]

fclean: clean
	@rm -fr $(NAME)
	@echo [CLEANING ... ]

re: fclean all
