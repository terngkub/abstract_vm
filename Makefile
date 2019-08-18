# Compiler Settings
CC			=	g++
CPP_VERSION	=	-std=c++17
CFLAGS		=	-Wall -Wextra -Werror $(CPP_VERSION) -g3

# Project Settings
NAME		=	avm
HEADER		=	ioperand.hpp \
				operand.hpp \
				factory.hpp \
				exception.hpp
FILE		=	main.cpp \
				factory.cpp \
				exception.cpp
SRC_DIR		=	src
INC_DIR		=	include
OBJ_DIR		=	obj

INC_FLAG	=	-I $(INC_DIR)
SRC			=	$(addprefix $(SRC_DIR)/,$(FILE))
INC			=	$(addprefix $(INC_DIR)/,$(HEADER))
OBJ			=	$(addprefix $(OBJ_DIR)/,$(FILE:%.cpp=%.o))

# Rules

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJ) $(INC)
	$(CC) $(CFLAGS) $(INC_FLAG) -o $(NAME) $(OBJ)

$(OBJ_DIR):
	mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.cpp
	$(CC) $(CFLAGS) $(INC_FLAG) -c -o $@ $<

clean:
	rm -rf $(OBJ_DIR)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re