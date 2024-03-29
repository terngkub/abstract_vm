# Compiler Settings
CC			=	g++
CPP_VERSION	=	-std=c++1z
CFLAGS		=	-Wall -Wextra -Werror $(CPP_VERSION)

# Project Settings
NAME		=	avm
HEADER		=	exception.hpp \
				factory.hpp \
				instruction.hpp \
				ioperand.hpp \
				lexer.hpp \
				operand_type.hpp \
				operand.hpp \
				parser.hpp \
				token.hpp \
				virtual_machine.hpp
FILE		=	exception.cpp \
				factory.cpp \
				instruction.cpp \
				lexer.cpp \
				main.cpp \
				operand_type.cpp \
				parser.cpp \
				token.cpp \
				virtual_machine.cpp
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