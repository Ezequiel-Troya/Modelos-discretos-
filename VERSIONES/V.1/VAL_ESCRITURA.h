#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;

bool esEntero(const string& input) {
    if (input.empty()) {
        cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
        return false;
    }

    int start = (input[0] == '-' || input[0] == '+') ? 1 : 0;
    for (int i = start; i < input.size(); ++i) {
        if (!isdigit(input[i])) {
            cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
            return false;
        }
    }

    return true;
}

bool esFlotante(const string& input) {
    istringstream iss(input);
    float f;
    char c;
    if ((iss >> f) && !(iss >> c)) {
        return true;
    } else {
        cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
        return false;
    }
}

bool esDouble(const string& input) {
    istringstream iss(input);
    double d;
    char c;
    if ((iss >> d) && !(iss >> c)) {
        return true;
    } else {
        cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
        return false;
    }
}

bool esChar(const string& input) {
    if (input.size() == 1) {
        return true;
    } else {
        cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
        return false;
    }
}

bool esBool(const string& input) {
    string lower;
    for (char c : input) lower += tolower(c);
    if (lower == "true" || lower == "false" || lower == "1" || lower == "0") {
        return true;
    } else {
        cout << "No se acepta ese tipo de dato. Vuelva a intentarlo." << endl;
        return false;
    }
}
