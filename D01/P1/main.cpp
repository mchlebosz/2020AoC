#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
	// open file for reading
	string line;
	vector<int> data;
	ifstream input("input.txt");
	if (input.is_open()) {
		while (getline(input, line)) data.push_back(stoi(line, nullptr, 10));

		input.close();
	}
	// open file for writing

	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < data.size() - 1; i++) {
		for (int j = i + 1; j < data.size(); j++) {
			if (data[i] + data[j] == 2020) {
				output << data[i] * data[j] << "\n";
			}
		}
	}

	output.close();

	return 0;
}