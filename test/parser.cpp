#include <iostream>
#include <stack>
#include <string>
#include <cctype>

// Node representing an operation or operand in the expression tree
struct Node {
    char data; // Operator or operand
    Node* left; // Left child
    Node* right; // Right child

    // Constructor for leaf nodes (operands)
    Node(char data) : data(data), left(nullptr), right(nullptr) {}

    // Constructor for internal nodes (operators)
    Node(char data, Node* left, Node* right) : data(data), left(left), right(right) {}
};

class Parser {
public:
    Node* parse(const std::string& expression) {
        std::stack<Node*> stack;

        for (char token : expression) {
            if (isdigit(token)) {
                stack.push(new Node(token));
            } else if (isOperator(token)) {
                Node* right = stack.top();
                stack.pop();
                Node* left = stack.top();
                stack.pop();
                stack.push(new Node(token, left, right));
            }
        }

        // The final result is at the top of the stack
        return stack.top();
    }

    // Utility function to check if a character is an operator
    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }
};

// Utility function to print the expression tree in infix notation
void printInfix(Node* node) {
    if (node) {
        if (node->left || node->right) {
            std::cout << "(";
        }
        printInfix(node->left);
        std::cout << node->data << " ";
        printInfix(node->right);
        if (node->left || node->right) {
            std::cout << ")";
        }
    }
}

int main() {
    Parser parser;
    std::string expression = "5 + (3 * 2)"; // Infix notation: 5 + (3 * 2)
    Node* root = parser.parse(expression);

    std::cout << "Infix notation: ";
    printInfix(root);

    // You can traverse the tree and perform operations as needed
    // For example, you can recursively evaluate the tree to get the result

    // Don't forget to deallocate memory to avoid memory leaks
    // (This part is not implemented in this example for simplicity)

    return 0;
}

