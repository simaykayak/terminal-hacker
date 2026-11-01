#include "Input.h"

#include <iostream>
#include <sstream>

using namespace std;

bool readNumber(int& value) {
    string line;

    while (getline(cin, line)) {
        istringstream input(line);
        char extra;

        if ((input >> value) && !(input >> extra)) {
            return true;
        }

        cout << "Please enter one whole number: ";
    }

    return false;
}

bool readText(string& value) {
    return static_cast<bool>(getline(cin, value));
}