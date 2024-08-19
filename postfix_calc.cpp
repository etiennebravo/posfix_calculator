/// @file postfixcalc.cpp
/// @author Etienne Bravo
/// @date 12/4/2023
/// @note Revised in 8/17/2024, now supports numbers of any length, negative numbers and user input.
/// @note I pledge my word of honor that I have complied with the
/// CSN Academic Integrity Policy while completing this assignment.

#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <cctype>
#include "Stack.hpp"

/// @brief Converts an Infix expression to a Postfix expression.
///
/// This function takes an Infix expression as input and converts it to
/// its equivalent Postfix expression using a stack-based approach. The
/// Infix expression should only contain operands, arithmetic operators
/// (+, -, *, /, %), and parentheses. Operands and operators in the input
/// string must be separated by at least one space.
///
/// @param infix The string containing the Infix expression.
/// @return std::string A string containing the Postfix expression.
///
/// @note The function assumes that the Infix expression is well-formed
/// and valid. Error handling for invalid expressions is not implemented.
///
/// Example Usage:
/// @code
///   std::string infix = "2 + 3 * 4";
///   std::string postfix = infix2postfix(infix);
///   std::cout << "Postfix: " << postfix << std::endl; // Outputs: 2 3 4 * +
/// @endcode

std::string infix2postfix(const std::string &infix);

/// @brief Evaluates a Postfix expression and returns its value.
///
/// This function takes a Postfix expression as input and evaluates it to
/// return its integer value. The Postfix expression should contain only
/// integer operands and standard arithmetic operators (+, -, *, /). Each
/// operand and operator in the input string must be separated by at least
/// one space.
///
/// @param postfix The string containing the Postfix expression.
/// @return int The integer value of the evaluated Postfix expression.
///
/// @note The function assumes that the Postfix expression is well-formed
/// and valid. Error handling for invalid expressions, such as division by
/// zero or malformed inputs, is not implemented.
///
/// Example Usage:
/// @code
///   std::string postfix = "2 3 4 * +";
///   int result = eval_postfix(postfix);
///   std::cout << "Result: " << result << std::endl; // Outputs: 14
/// @endcode

int eval_postfix(const std::string &postfix);

/// @brief Evaluates precedence of the entered operator
/// @param op Operator
/// @return precedence Determines precedence of the operator
int precedence(char op);

/// @brief Evaluates if the string contains only operators and numbers
/// @param str string containing input
/// @return true if it contains only numbers and valid operators
/// @note This does not check for a valid format in the input. In the user we trust :D
bool containsOnlyValidChars(std::string const &str);

int main(int argc, char* argv[])
{
    std::string input;
    std::string postfix;
    int ans;
    size_t count = 1;

    if (argc > 1) {
        std::ifstream inputFile(argv[1]); // Open the file
        if (!inputFile)
        {
            std::cerr << "Unable to open file input.txt";
            return 1; // Return an error code
        }

        while (std::getline(inputFile, input))
        {
            postfix = infix2postfix(input);
            ans = eval_postfix(postfix);
            std::cout << "Case " << count << ": " << ans << std::endl;
            count++;
        }

        inputFile.close();
    } 
    
    else {
        do {
            std::cout << "--------------------------------------------------------------------------------" << std::endl;
            std::cout << "Enter \"EXIT\" to end the program." << std::endl;
            std::cout << "Enter \"HELP\" to see rules for input." << std::endl;
            std::cout << "Example formula: ( ( -500 + 400 ) * ( -300 - 200 ) / ( -100 / ( 0 + 100 ) ) )" << std::endl;
            std::cout << "Enter a formula: " << std::endl;
            std::getline(std::cin, input);
            std::cout << std::endl;

            // Help menu
            if (input == "HELP" || input == "help") {
                std::cout << "--------------------------------------------------------------------------------" << std::endl;
                std::cout << "RULES:" << std::endl;
                std::cout << "1. Only these signs are accepted '(' , ')' , '+', '-', '/', '*', '%'" << std::endl;
                std::cout << "2. Operators '(' , ')' , '+', '-', '/', '*', '%' need to be separated by spaces." << std::endl;
                std::cout << "3. Only integers (whole numbers) can be handled." << std::endl;
                std::cout << "3. Negative numbers have their sign next to them e.g: -100, -200, -500" << std::endl;
                std::cout << "4. Numbers greater than 9 digits cannot be used." << std::endl;
                std::cout << std::endl;
            } 

            // Evaluate formula
            else if (containsOnlyValidChars(input)) {
                postfix = infix2postfix(input);
                ans = eval_postfix(postfix);
                std::cout << "YOU ENTERED: " << input << std::endl;
                std::cout << "RESULT: " << ans << std::endl;
            }

            // invalid input 
            else if (input != "EXIT" && input != "exit") {
                std::cout << "Invalid character was found." << std::endl;
            }

        } while (input != "EXIT" && input != "exit");
    }

    return 0;
}

// valid chars also include spaces
bool containsOnlyValidChars(std::string const &str) {
    return str.find_first_not_of(" 1234567890()+-/*%") ==
        std::string::npos;
}

int precedence(char op)
{
    if (op == '+' || op == '-')
    {
        return 1;
    }
    if (op == '*' || op == '/' || op == '%')
    {
        return 2;
    }
    return 0;
}

std::string infix2postfix(const std::string &infix)
{
    std::string postfix;
    Stack<char> stack;

    std::istringstream iss(infix);
    char token;

    // populate string
    while (iss >> token)
    {
        // Numbers and negative numbers
        if (std::isdigit(token) || (token == '-' && isdigit(iss.peek())) )
        {
            std::string number;
            if (token == '-')
            {
                number += token;
                iss >> token;
            }
            while (std::isdigit(token))
            {
                number += token;
                if (!(iss >> token))
                    break;
            }
            iss.putback(token);
            postfix += number + ' ';
        }

        // Open parenthesis
        else if (token == '(')
        {
            stack.push(token);
        }

        // If close parenthesis
        else if (token == ')')
        {
            while (!stack.empty() && stack.top() != '(')
            {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            stack.pop();
        }

        // If operator is found
        else
        {
            while (!stack.empty() && precedence(token) <= precedence(stack.top()))
            {
                postfix += stack.top();
                postfix += ' ';
                stack.pop();
            }
            stack.push(token);
        }
    }

    // clear the stack when input ends
    while (!stack.empty())
    {
        postfix += stack.top();
        postfix += ' ';
        stack.pop();
    }

    return postfix;
}

int eval_postfix(const std::string &postfix)
{
    Stack<int> stack;
    std::istringstream iss(postfix);
    std::string token;

    while (iss >> token) {
        if (std::isdigit(token[0]) || (token[0] == '-' && token.length() > 1)) {
            stack.push(std::stoi(token));
        } else {
            int operand1 = stack.top();
            stack.pop();
            int operand2 = stack.top();
            stack.pop();

            switch (token[0]) {
                case '+':
                    stack.push(operand2 + operand1);
                    break;
                case '-':
                    stack.push(operand2 - operand1);
                    break;
                case '*':
                    stack.push(operand2 * operand1);
                    break;
                case '/':
                    stack.push(operand2 / operand1);
                    break;
                case '%':
                    stack.push(operand2 % operand1);
                    break;
                default:
                    std::cerr << "Unknown operator: " << token[0] << std::endl;
                    break;
            }
        }
    }

    return stack.top();
}