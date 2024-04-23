#include <iostream>
#include <string>
#include <cmath>
using namespace std;

string in() {
    string temp;
    string s = "";

    while (true) {
        cin >> temp;
        
        if (temp == "exit") {break;}
        s += temp;

        cout << "!" << s << endl;

    }

    return s;
}

int main() {
    string s;
    s = in();
    cout << s;
    return 0;
}