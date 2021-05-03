AST_SRC := $(shell find AST/AST -name "*.cpp")

all:
	flex -o scanner.cpp scanner.l
	bison -o parser.cpp parser.y
	g++ -g driver.cpp scanner.cpp parser.cpp main.cpp $(AST_SRC)  -o a.out

clean:
	rm -rf a.out scanner.cpp parser.cpp parser.hpp location.hh 