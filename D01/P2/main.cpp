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
	for (int i = 0; i < data.size() - 2; i++) {
		for (int j = i + 1; j < data.size() - 1; j++) {
			for (int k = j + 1; k < data.size(); k++) {
				if (data[i] + data[j] + data[k] == 2020)
					output << data[i] * data[j] * data[k] << "\n";
			}
		}
	}

	output.close();

	return 0;
}