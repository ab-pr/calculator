#include <iostream>
#include <string>
#include <cctype>
#include <ctype.h>
#include <map>
#include "../muparser/muParser.h"
using namespace std;

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define RED_BACKGROUND "\033[41m"
#define BLUE_BACKGROUND "\033[44m"

#define YELLOW "\033[33m"
#define WHITE "\033[37m"
#define RESET   "\033[0m"
#define GREEN   "\033[32m"
#define RED     "\033[31m"

map<string, double> setVariables(map<string, double> variables);
string parseVariablesToInt(map<string, double> variables, string equaition);
double parseStringMap(const string& equation, const map<string, double>& variables);
int calculate(map<string, double> variables);
string input();
string options();
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
        else if     (option == "STOP") { ext(); }
    }
}


map<string, double> setVariables(map<string, double> variables) {
	string input;
	string num = "";
	string variable;
	cout << BLUE_BACKGROUND << YELLOW << "\n\n" << "Enter values for each variable eg. 'a=5'\n.To output the variables, type 'PRINT'\n.To stop, type 'STOP', and to clear all variables, type 'CLEAR'." << '\n' << RESET << "\n\n"; cout << '\n';
	
	while (true) {
        cout << YELLOW << "--> " << RESET;
		cin >> input;
	
		// Removes spaces from input
		input.erase(remove_if(input.begin(), input.end(), [](char c) { return isspace(c); }), input.end());

		if (input == "STOP") { break; }
	
		else if (input == "PRINT") {
			cout << '\n';
			for (const auto& pair : variables) {
				cout << pair.first << "=" << pair.second << '\n';
			} cout << '\n';

		} else if (isalpha(input[0]) && input[1] == '=' && isdigit(input[2])){

			variable = input[0];
			for (int i = 0; i < input.size(); i++) {
				if (isdigit(input[i])) {
					num += input[i];
				}
			}
			double numd = stod(num)+0.0;

			variables[variable] = numd;
			cout << variable << '\t' << numd << '\n';

		} else if (input == "CLEAR") {
			cout << RED_BACKGROUND << WHITE << "SURE? THIS WILL CLEAR ALL VARIABLE DATA! (YES/NO))" << '\n';
			cin >> input;

			if (input == "YES") { variables.clear(); cout << RED_BACKGROUND  << WHITE << "CLEARED." << RESET << '\n';}
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


string parseVariablesToInt(map<string, double> variables, string equation) {
    string result = equation;

    for (const auto& pair : variables) {
        size_t pos = result.find(pair.first);
        while (pos != string::npos) {
            ostringstream oss;
            oss << pair.second;
            string valueStr = oss.str();

            result.replace(pos, pair.first.length(), valueStr);

            pos = result.find(pair.first, pos + valueStr.length());
        }
    }

    return result;
}


double parseStringMap(const string& equation, const map<string, double>& variables) {
    try {
        mu::Parser parser;
        parser.SetExpr(equation);

        return parser.Eval();
    }
    catch (mu::Parser::exception_type &e) {
        cout << e.GetMsg() << '\n';
        return NAN;
    }
}


int calculate(map<string, double> variables) {
    string equation;
    string calculation;
    double result;

    cout << '\n' << BLUE_BACKGROUND << WHITE <<

    "\n\nStart writing your calculations here.\n" <<
    "To exit calculator and go back to menu type 'STOP':\n"
	<< RESET << "\n\n";

    while (true) {
        cout << RED << "--> " << RESET;
        cin >> equation;
        if (equation == "STOP") { break; }

		equation = parseVariablesToInt(variables, equation);

		result = parseStringMap(equation, variables);
		cout << GREEN << result << RESET << '\n';
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
        << "STOP\n" << RESET
        << "---> ";
        cin >> option;

        if (option != "CALC" && option != "VARIABLES" && option != "WIPE" && option != "STOP") { cout << RED_BACKGROUND << WHITE << "INVALID OPTION" << RESET << '\n'; }
    } while (option != "CALC" && option != "VARIABLES" && option != "WIPE" && option != "STOP");

    return option;
}


void wipe() {
    system(CLEAR_SCREEN);
}


void ext() {
	exit(0);
}