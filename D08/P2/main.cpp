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

int AccWithReplace(vector<command> operations, int rep) {
	vector<bool> visited(operations.size(), false);
	long accumulator = 0;
	int index        = 0;
	int moves        = 0;
	while (!visited[index]) {
		visited[index] = true;

		if (moves == rep) {
			moves++;
			if (operations[index].name == "jmp") {
				index++;

			} else if (operations[index].name == "nop") {
				index += operations[index].move;
				continue;
			} else if (operations[index].name == "nop") {
				return -66666666;
			}
		} else {
			moves++;
			if (operations[index].name == "jmp") {
				index += operations[index].move;
				continue;
			}
			if (operations[index].name == "acc") {
				accumulator += operations[index].move;
			}
			index++;
		}
	}
	if (index > operations.size())
		return accumulator;
	else
		return -66666666;
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
	vector<command> operations;
	for (int i = 0; i < data.size(); i++) {
		string name = data[i].substr(0, data[i].find(" "));
		int value   = stoi(data[i].substr(data[i].find(" ")), nullptr, 10);
		operations.push_back(command(name, value));
	}
	vector<bool> visited(operations.size(), false);
	long accumulator = 0;
	int index        = 0;
	int moves        = 0;
	while (!visited[index]) {
		moves++;
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
	for (int j = 0; j < moves - 1; j++) {
		int acc = AccWithReplace(operations, j);

		if (acc != -66666666) {
			cout << acc << "; <  ";
			break;
		}
	}

	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < operations.size(); i++) {
		output << "[ " << visited[i] << " , " << operations[i].name << " , "
			   << operations[i].move << " ]\n";
	}
	cout << accumulator << " i:" << index << " m:" << moves;

	output.close();

	return 56;
}