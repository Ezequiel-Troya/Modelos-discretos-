#include <iostream>
#include <string>
#include <sstream>
#include <cctype>
#include <limits>

using namespace std;
bool esEntero(const string& input) {
    if (input.empty()) return false;
    int start = (input[0] == '-' || input[0] == '+') ? 1 : 0;
    for (int i = start; i < input.size(); ++i) {
        if (!isdigit(input[i])) return false;
    }
    return true;
}

bool esFlotante(const string& input) {
    istringstream iss(input);
    float f;
    char c;
    return (iss >> f) && !(iss >> c);
}

bool esDouble(const string& input) {
    istringstream iss(input);
    double d;
    char c;
    return (iss >> d) && !(iss >> c);
}
bool esChar(const string& input) {
    return input.size() == 1;
}
bool esBool(const string& input) {
    string lower;
    for (char c : input) lower += tolower(c);
    return (lower == "true" || lower == "false" || lower == "1" || lower == "0");
}
