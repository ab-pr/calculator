#include <iostream>
#include <cmath>
#include <ctype.h>
using namespace std;

#ifdef _WIN32
    #define CLEAR_SCREEN "cls"
#else
    #define CLEAR_SCREEN "clear"
#endif

#define RESET   "\033[0m"
#define RED     "\033[31m"
#define GREEN   "\033[32m"
#define BLUE    "\033[34m"

float calculate();
string input();
string options();
void wipe();
void ext();

int main() {
    string option;
    while (true) {
        option = options();

        if          (option == "c") { calculate(); }
        else if     (option == "w") { wipe(); }
        else if     (option == "e") { ext(); }
    }
}


float calculate() {
    long double result;
    return result;
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
        cout << "Enter option ("
        << RED << "(c)" << RESET "alculate), "
        << GREEN << "(w)" << RESET << "ipe) screen, "
        << BLUE << "(e)" << RESET << "xit program): ";
        cin >> option;

        if (option != "c" && option != "w" && option != "e") { cout << RED << "INVALID OPTION" << RESET << '\n'; }
    } while (option != "c" && option != "w" && option != "e");

    return option;
}

void wipe() {
    system(CLEAR_SCREEN);
}

void ext() { exit(0); }