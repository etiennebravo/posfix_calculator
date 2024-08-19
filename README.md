# INFIX TO POSTFIX CALCULATOR

Created by [Etienne Bravo]
Project outline and test file provided by: Kevin Mess <kevin.mess@csn.edu>

This project converts infix expressions to postfix notation and evaluates the resulting postfix expressions.
It supports basic arithmetic operations and handles parentheses.

Example formula: ( ( -500 + 400 ) * ( -300 - 200 ) / ( -100 / ( 0 + 100 ) ) ) = -500 400 + -300 200 - * -100 0 100 + / / =  -50000

## Installation:
  1. Clone the repository.
  2. Navigate to the directory.
  3. Compile the source.
  4. Run the executable. (run normally if user input is desired, run with text file if desired).
  e.g: .\postfix_calc.exe or .\postfix_calc.exe input.txt

## Note: Makefile included for easier compile and run processes.
## Make:
   all : compiles all files and generates executable file.
   run : runs the program no input file.
   runFile : runs the program with input.txt.

## Features:
  1. Convertion of infix to postfix.
  2. Postfix evaluation.
  3. User or file input.
  4. Stack and List classes created by me.

## Limitations: 
  1. Only these signs are accepted '(' , ')' , '+', '-', '/', '*', '%' 
  2. Operators '(' , ')' , '+', '-', '/', '*', '%' need to be separated by spaces.
  3. Only integers (whole numbers) can be handled.
  4. Negative numbers must have their sign next to them e.g: -100, -200, -500.
  5. Operations that result in numbers greater than 10 digits break the program.

## Future plans:
  1. Adding proper error handling.
  2. A graphical interfase for ease of use.
  3. Maybe making a website for people to use this, maybe.

Contributions are welcome!
I'm new to github but i'll see what I can do.

This project is licensed under the MIT License - see the LICENSE file for details.
