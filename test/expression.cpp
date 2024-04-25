#include <sstream>
#include <stack>

// Function to check if a character is an operator
bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

// Function to check if a character is a digit
bool isDigit(char c) {
    return isdigit(c);
}

// Function to evaluate arithmetic expressions
double evaluateExpression(const string& expression) {
    stringstream ss(expression);
    stack<double> operands;
    stack<char> operators;

    char token;
    while (ss >> token) {
        if (token == '(') {
            operators.push(token);
        } else if (token == ')') {
            while (operators.top() != '(') {
                char op = operators.top();
                operators.pop();

                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();

                if (op == '+')
                    operands.push(a + b);
                else if (op == '-')
                    operands.push(a - b);
                else if (op == '*')
                    operands.push(a * b);
                else if (op == '/')
                    operands.push(a / b);
            }
            operators.pop(); // Remove '('
        } else if (token == 's') {
            operators.push(token);
        } else if (isOperator(token)) {
            while (!operators.empty() && operators.top() != '(' && ((token != '*' && token != '/') || (operators.top() == '*' || operators.top() == '/'))) {
                char op = operators.top();
                operators.pop();

                double b = operands.top();
                operands.pop();
                double a = operands.top();
                operands.pop();

                if (op == '+')
                    operands.push(a + b);
                else if (op == '-')
                    operands.push(a - b);
                else if (op == '*')
                    operands.push(a * b);
                else if (op == '/')
                    operands.push(a / b);
            }
            operators.push(token);
        } else if (isDigit(token)) {
            ss.putback(token);
            double number;
            ss >> number;
            operands.push(number);
        }
    }

    while (!operators.empty()) {
        char op = operators.top();
        operators.pop();

        double b = operands.top();
        operands.pop();
        double a = operands.top();
        operands.pop();

        if (op == '+')
            operands.push(a + b);
        else if (op == '-')
            operands.push(a - b);
        else if (op == '*')
            operands.push(a * b);
        else if (op == '/')
            operands.push(a / b);
        else if (op == 's')
            operands.push(sqrt(b));
    }

    return operands.top();
}

int main() {
    string expression = "(4 + 4) * 3 - s4";
    double result = evaluateExpression(expression);
    cout << "Result: " << result << endl;

    return 0;
}
