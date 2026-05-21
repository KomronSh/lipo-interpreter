#include <fstream>
#include <string>
#include <stack>
#include "Lexem_struct.h"
#include "syntax_analyzer.h"

ifstream inlex("lexem.txt");
ofstream out("postfix_form.txt");

bool postfix_record();

bool read() {
    if (inlex >> lex.line >> lex.value >> lex.type) {
        return true;
    }
    return false;
}

void console_out() {
    ifstream in("postfix_form.txt");
    string line;
    while (getline(in, line)) {
        cout << line << endl;
    }
    in.close();
}

int priority(const string& value) {
    if (value == "NOT") return 3;
    if (value == "AND") return 2;
    if (value == "OR" || value == "XOR") return 1;
    return 0;
}

void pop_operators(stack<string>& operators) {
    while (!operators.empty()) {
        if (operators.top() != "(") {
            out << operators.top() << " ";
        }
        operators.pop();
    }
}

bool priorityAnalysis() {
    if (!syntax_analysis()) {
        cout << "Синтаксический анализ завершён с ошибками\n";
        logFile << "Синтаксический анализ завершён с ошибками\n";
        return false;
    }

    inlex.clear();           
    inlex.seekg(0);          

    if (!postfix_record()) return false;
    cout << "Приоритетный анализ завершён успешно\n";
    logFile << "Приоритетный анализ завершён успешно\n";
    return true;
}

bool postfix_record() {
    if (!inlex.is_open()) {
        cout << "Ошибка: не удалось открыть файл лексем\n";
        logFile << "Ошибка: не удалось открыть файл лексем\n";
        return false;
    }

    stack<string> operators;
    string leftOperand = {""};
    bool isExpression = false;

    while (read()) {
        if (lex.type == "Identifier") {
            if (isExpression) {
                out << lex.value << " ";
            }
            else {
                leftOperand = lex.value;
            }
        }
        else if (lex.type == "equal") {
            out << leftOperand << " ";
            isExpression = true;
        }
        else if (lex.type == "constTrue" || lex.type == "constFalse") {
            out << lex.value << " ";
        }
        else if (lex.type == "binaryNot" ||
            lex.type == "binaryAND" ||
            lex.type == "binaryOR" ||
            lex.type == "unaryOperand") {

            bool isRightAssociative = false;
            if (lex.value == "NOT") isRightAssociative = true;


            while (!operators.empty() &&
                operators.top() != "(" &&
                (isRightAssociative
                    ? priority(operators.top()) > priority(lex.value)
                    : priority(operators.top()) >= priority(lex.value))) {

                out << operators.top() << " ";
                operators.pop();
            }
            operators.emplace(lex.value);
        }
        else if (lex.type == "parenthLeft") {
            operators.emplace("(");
        }
        else if (lex.type == "parenthRight") {
            while (!operators.empty() && operators.top() != "(") {
                out << operators.top() << " ";
                operators.pop();
            }
            if (!operators.empty() && operators.top() == "(") {
                operators.pop();
            }
        }
        else if (lex.type == "lineEnd" && isExpression) {
            pop_operators(operators);
            out << "= \n";
            isExpression = false;
        }
    }


    inlex.close();
    out.close();
    return true;
}
