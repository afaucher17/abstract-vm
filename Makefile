CXX = g++

CXXFLAGS = -Wall -Werror -Wextra -g -std=c++98 -pedantic-errors

SOURCES = AbstractVM.cpp \
		  FileManager.cpp \
		  Tokenizer.cpp \
		  Token.cpp \
		  Analyzer.cpp \
		  Calculator.cpp \
		  Double.cpp \
		  Float.cpp \
		  Int8.cpp \
		  Int16.cpp \
		  Int32.cpp \
		  Instruction.cpp \
		  InstructionFactory.cpp \
		  OperandFactory.cpp \
		  Parser.cpp \
		  main.cpp \

OBJECTS = $(SOURCES:.cpp=.o)

NAME = avm

all: $(NAME)

$(NAME): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(NAME)

clean:
	rm -f $(OBJECTS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: re clean fclean all
