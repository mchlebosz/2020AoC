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

struct command {
	string name;
	int move;
	command(string _name, int _move) {
		name = _name;
		move = _move;
	}
};

int main() {
	// open file for reading
	string line;
	vector<string> data;
	ifstream input("input.txt");
	if (input.is_open()) {
		while (getline(input, line)) data.push_back(line);
		input.close();
	}
	vector<command> operations;
	for (int i = 0; i < data.size(); i++) {
		string name = data[i].substr(0, data[i].find(" "));
		int value   = stoi(data[i].substr(data[i].find(" ")), nullptr, 10);
		operations.push_back(command(name, value));
	}
	vector<bool> visited(operations.size(), false);
	long accumulator = 0;
	int index        = 0;

	while (!visited[index]) {
		visited[index] = true;
		if (operations[index].name == "jmp") {
			index += operations[index].move;
			continue;
		}
		if (operations[index].name == "acc") {
			accumulator += operations[index].move;
		}
		index++;
	}

	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < operations.size(); i++) {
		output << "[ " << visited[i] << " , " << operations[i].name << " , "
			   << operations[i].move << " ]\n";
	}
	cout << accumulator;

	output.close();

	return 56;
}