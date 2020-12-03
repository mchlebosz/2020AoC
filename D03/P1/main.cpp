#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int countTrees(vector<string> map, int x, int y) {
	int currX      = 0;
	int currY      = 0;
	int countTrees = 0;
	while (currY < map.size()) {
		if (currX >= map[currY].length()) currX = currX - map[currY].length();
		if (map[currY][currX] == '#') countTrees++;
		currY += y;
		currX += x;
	}
	return countTrees;
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

	ofstream output;
	output.open("output.txt");
	int amount = countTrees(data, 3, 1);
	output << amount;

	output.close();

	return 0;
}