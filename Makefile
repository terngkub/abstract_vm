# Compiler Settings
CC = g++
CPP_VERSION = -std=c++17
CFLAGS = -Wall -Wextra -Werror $(CPP_VERSION) -g3

# Project Settings
NAME = avm
FILE =	main.cpp \
		OperandFactory.cpp
SRC_DIR = src
SRC = $(addprefix $(SRC_DIR)/,$(FILE))
INC = -I include
OBJ_DIR = obj
OBJ = $(addprefix $(OBJ_DIR)/,$(FILE:%.cpp=%.o))

# Rules

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ)
	$(CC) $(CFLAGS) $(INC) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re