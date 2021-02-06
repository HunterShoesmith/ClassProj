FLAGS = -Wall -Wextra -Wfloat-equal -Wundef -Wcast-align -Wwrite-strings -Wredundant-decls -Wshadow -Woverloaded-virtual
CC = g++

go: calculator.o calculator.o ExpressionTree.o BinaryTree.o ExpressionTools.o
	$(CC) -o go calculator.o ExpressionTree.o BinaryTree.o ExpressionTools.o
	@echo "Everything linked"

calculator.o : calculator.cpp
	$(CC) $(FLAGS) -c calculator.cpp
	@echo "calculator compiled successfully"

ExpressionTree.o : ExpressionTree.cpp
	$(CC) $(FLAGS) -c ExpressionTree.cpp
	@echo "ExpressionTree compiled successfully"

BinaryTree.o : BinaryTree.cpp 
	$(CC) $(FLAGS) -c BinaryTree.cpp
	@echo "BinaryTree compiled successfully"

ExpressionTools.o : ExpressionTools.cpp
	$(CC) $(FLAGS) -c ExpressionTools.cpp
	@echo "ExpressionTools compiled successfully"

clean:
	rm -f core *.o go
