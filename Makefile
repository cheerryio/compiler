AST_SRC := $(shell find AST/AST -name "*.cpp")
AST_VISITOR_SRC := $(shell find AST/ASTVisitor -name "*.cpp")
AST_VISITOR_SRC := $(filter-out AST/ASTVisitor/main.cpp, $(AST_VISITOR_SRC))
MAIN_SRC = driver.cpp scanner.cpp parser.cpp main.cpp

INC = -IAST/AST -IAST/ASTVisitor

a.out:$(MAIN_SRC) $(AST_SRC) $(AST_VISITOR_SRC)
	g++ -g $(MAIN_SRC) $(AST_SRC) $(AST_VISITOR_SRC) $(INC) -o a.out

scanner.cpp:scanner.l
	flex scanner.l -o scanner.cpp

parser.cpp:parser.y
	bison -v -o parser.cpp parser.y

clean:
	rm -rf a.out scanner.cpp parser.cpp parser.hpp location.hh 