#include <fstream>
#include <string>
#include <sstream>
#include "postfix_analyzer.h"

using namespace std;

bool mnimocoder() {
	ifstream in("postfix_form.txt");
	ofstream out("mnimocode.txt");
	if (!in.is_open() || !out.is_open()) {
		cout << "File is not found!\n";
		return false;
	}
	
	string word;
	stringstream ss;
	vector <string> variables;

	ss << in.rdbuf();
	while (ss>>word) {
		if (word=="XOR") out << "XOR " <<"\n";
		else if (word=="OR") out << "OR " <<"\n";
		else if (word=="AND") out << "AND " <<"\n";
		else if (word=="NOT") out << "NOT " <<"\n";
		else if (isdigit(word[0])) out << "LIT " << word << "\n";
		else if (isalpha(word[0])) {
			variables.push_back(word);
			out << "LOAD " << word << "\n";
		}
		else if (word == "=") {
			out << "STO " << variables[0] << "\n";
			variables.clear();	
		}
	}
	in.close();
	out.close();
	return true;
}

bool buildMnimocode() {
	if (!priorityAnalysis()) return false;
	if (!mnimocoder()) return false;
	return true;
}