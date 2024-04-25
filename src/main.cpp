#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include "../headers/exprtk.hpp"
using namespace std;

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

typedef exprtk::symbol_table<double> symbol_table_t;
typedef exprtk::expression<double> expression_t;
typedef exprtk::parser<double> parser_t;

#define RED_BACKGROUND "\033[41m"
#define BLUE_BACKGROUND "\033[44m"

#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

string input();
string options();
map<string, double> setVariables(map<string, double> variables);
float parser(string equation, map<string, double> variables);
int calculate(map<string, double> variables);
void wipe();
void ext();

int main() {
    string option;
	map<string, double> variables;
    while (true) {
        option = options();

        if          (option == "CALC") { calculate(variables); }
		else if 	(option == "VARIABLES") { variables = setVariables(variables); }
        else if     (option == "WIPE") { wipe(); }
        else if     (option == "EXIT") { ext(); }
    }
}

map<string, double> setVariables(map<string, double> variables) {
	string input;
	string num = "";
	string variable;
	cout << BLUE_BACKGROUND << YELLOW << "\n\n" << "Enter values for each variable eg. 'a=5'\n.To output the variables, type 'PRINT'\n.To stop, type 'STOP', and to clear all variables, type 'CLEAR'." << "\n" << RESET << "\n\n"; cout << "\n";
	
	while (true) {
        cout << YELLOW << "--> " << RESET;
		cin >> input;
	
		// Removes spaces from input
		input.erase(remove_if(input.begin(), input.end(), [](char c) { return isspace(c); }), input.end());

		if (input == "STOP") { break; }
	
		else if (input == "PRINT") {
			cout << "\n";
			for (const auto& pair : variables) {
				cout << pair.first << "=" << pair.second << "\n";
			} cout << "\n";

		} else if (isalpha(input[0]) && input[1] == '=' && isdigit(input[2])){

			variable = input[0];
			for (int i = 0; i < input.size(); i++) {
				if (isdigit(input[i])) {
					num += input[i];
				}
			}
			variables[variable] = stod(num);
		} else if (input == "CLEAR") {
			cout << RED_BACKGROUND << WHITE << "SURE? THIS WILL CLEAR ALL VARIABLE DATA! (YES/NO))" << "\n";
			cin >> input;

			if (input == "YES") { variables.clear(); cout << RED_BACKGROUND  << WHITE << "CLEARED." << RESET << "\n";}
		}
		

		else {
			cout << RED_BACKGROUND << WHITE << "REMEMBER,\n 1st char must be a single char,\n 2nd char must be '=',\n3rd char must be a digit (eg. '3') and,\nYou must use the, STOP, PRINT, CLEAR operators" << RESET;
		}
		input = "";
		num = "";
		variable = "";

	}

	
	return variables;
}

float parser(string equation, map<string, double> variables) {
	symbol_table_t symbol_table;
    expression_t expression;
    parser_t parser;

	for (auto i : variables) { symbol_table.add_variable(i.first, i.second); }
	expression.register_symbol_table(symbol_table);
	parser.compile(equation, expression);

	return (double) expression.value();
}

int calculate(map<string, double> variables) {
    string input;
    string calculation;
    long double result;

    cout << "\n" << BLUE_BACKGROUND << WHITE <<

    "\n\nStart writing your calculations here.\n" <<
    "To exit calculator and go back to menu type 'STOP':\n"
	<< RESET << "\n\n";

    while (true) {
        cout << RED << "--> " << RESET;
        cin >> input;
        if (input == "STOP") { break; }

		result = parser(input, variables);
		cout << GREEN << result << RESET << "\n";
		variables["ANS"] = result;
    }
	return 2; // Unknow Break
}

string input() {
    string operation;

    cout << "Enter an operation: " << '\n';
    getline(cin, operation);

    return operation;
}

string options() {
    string option;

    do {
        cout << "Enter option:\n\n"
        << YELLOW << "CALC,\n"
		<< "VARIABLES,\n"
        << "WIPE,\n"
        << "EXIT\n" << RESET
        << "---> ";
        cin >> option;

        if (option != "CALC" && option != "VARIABLES" && option != "WIPE" && option != "EXIT") { cout << RED_BACKGROUND << WHITE << "INVALID OPTION" << RESET << '\n'; }
    } while (option != "CALC" && option != "VARIABLES" && option != "WIPE" && option != "EXIT");

    return option;
}

void wipe() {
    system(CLEAR_SCREEN);
}

void ext() {
	exit(0);
}
