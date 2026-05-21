#pragma once
#include <iostream>
using namespace std;
struct Lexem {
    int    line = -1;
    string value = {""};
    string type = {""};
};

Lexem lex;