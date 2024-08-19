.PHONY: clean

# build an executable
all: postfix_calc.cpp
	g++ -g -Wall *.cpp *.hpp -o postfix_calc

# Run with user input
run: postfix_calc
	./postfix_calc.exe

# Run with input file
run: postfix_calc
	./postfix_calc.exe input3.txt

clean: 
	$(RM) postfix_calc.exe
