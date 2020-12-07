#include <math.h>

#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

using namespace std;

int main() {
	// open file for reading
	string line;
	vector<string> data;
	ifstream input("input.txt");
	if (input.is_open()) {
		while (getline(input, line)) data.push_back(line);
		input.close();
	}
	vector<string> customs(0);
	for (int i = 0; i < data.size(); i++) {
		string temp = "";
		while (data[i] != "" && i < data.size()) {
			temp += data[i];
			i++;
		}
		customs.push_back(temp);
	}

	ofstream output;
	output.open("output.txt");

	int sum = 0;
	for (int i = 0; i < customs.size(); i++) { /* code */
		vector<bool> letters(26);
		fill(letters.begin(), letters.end(), false);
		for (int j = 0; j < customs[i].size(); j++) {
			letters[int(customs[i][j]) - 97] = true;
		}
		for (int j = 0; j < letters.size(); j++)
			if (letters[j] == true) sum++;
		output << customs[i] << ": " << sum << ";\n";
	}

	output << "sum = " << sum;

	output.close();

	return 56;
}