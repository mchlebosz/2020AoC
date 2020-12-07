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

int sum_group(vector<string> group) {
	int sum = 0;
	vector<int> letters(26);
	fill(letters.begin(), letters.end(), 0);

	for (int i = 0; i < group.size(); i++) {
		for (int j = 0; j < group[i].length(); j++) {
			letters[int(group[i][j]) - 97]++;
		}
	}
	for (int j = 0; j < letters.size(); j++)
		if (letters[j] == group.size()) sum++;
	return sum;
}

int main() {
	// open file for reading
	string line;
	vector<string> data;
	ifstream input("input.txt");
	if (input.is_open()) {
		while (getline(input, line)) data.push_back(line);
		input.close();
	}
	vector<vector<string> > customs(0);
	for (int i = 0; i < data.size(); i++) {
		vector<string> temp;
		while (data[i] != "" && i < data.size()) {
			temp.push_back(data[i]);
			i++;
		}
		customs.push_back(temp);
	}

	ofstream output;
	output.open("output.txt");

	int sum = 0;
	for (int i = 0; i < customs.size(); i++) { /* code */

		sum += sum_group(customs[i]);
		for (auto a : customs[i]) { output << a << ','; };
		output << " : " << sum << "\n";
	}

	cout << "sum = " << sum;

	output.close();

	return 56;
}