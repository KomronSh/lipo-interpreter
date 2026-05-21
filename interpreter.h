#pragma once
#include <iostream>
#include <stack>
#include <fstream>
#include <map>
#include <sstream>
#include <string>
#include "mnimocode_builder.h"


bool interpretMnimocode() {
	ifstream in("mnimocode.txt");
	if (!in.is_open()) {
		std::cout << "Не удалось открыть файл с мнимокодом\n";
		return false;
	}

    stack<int> st;
    map<string, int> vars;
    string line;

    while (getline(in, line)) {
        stringstream ss(line);
        string cmd;
        ss >> cmd;

        if (cmd == "LIT") {
            int value;
            ss >> value;
            st.push(value);
        }
        else if (cmd == "LOAD") {
            string var;
            ss >> var;
            st.push(vars[var]);
        }
        else if (cmd == "STO") {
            string var;
            ss >> var;
            vars[var] = st.top();
            st.pop();
        }
        else if (cmd == "OR") {
            int b{ st.top() }; st.pop();
            int a{ st.top() }; st.pop();
            st.push(a || b);
        }
        else if (cmd == "XOR") {
            int b{ st.top() }; st.pop();
            int a{ st.top() }; st.pop();
            st.push(a ^ b);
        }
        else if (cmd == "NOT") {
            int a{ st.top() }; st.pop();
            st.push(!a);
        }
        else if (cmd == "AND") {
            if (st.size() < 2) {
                int b{ st.top() }; st.pop();
                int a{ st.top() }; st.pop();
                st.push(a && b);
            }
        }
    }

    for (auto x : vars) {
        std::cout << x.first << " = " << x.second << std::endl;
    }

    in.close();
	return true; 
}

bool interpret()
{
    if (!buildMnimocode()) {
        std::cout << "Ошибка при генерации мнимокода\n";
        return false;
    }
    std::cout << "Генерация мнимокода завершена успешно\n";
    if (!interpretMnimocode()) return false;
    return true;
}