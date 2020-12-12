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

char rotate(char current_dir, int rotation) {
	int current_rotation = 360;
	switch (current_dir) {
		case 'W': current_rotation += 90;
		case 'S': current_rotation += 90;
		case 'E': current_rotation += 90;
		case 'N': current_rotation += 0;
	}
	current_rotation = (current_rotation + rotation) % 360;
	switch (current_rotation) {
		case 0: return 'N';
		case 90: return 'E';
		case 180: return 'S';
		case 270: return 'W';
	}
	return 'N';
}

struct coordinates {
	int north;
	int west;
	char direction;
};

coordinates modifyPos(string newPos, coordinates pos) {
	char command = newPos[0];
	int value    = stoi(newPos.substr(1), nullptr, 10);
	switch (command) {
		case 'F':
			switch (pos.direction) {
				case 'N': pos.north += value; break;
				case 'S': pos.north -= value; break;
				case 'E': pos.west -= value; break;
				case 'W': pos.west += value; break;
			}
			break;
		case 'R': pos.direction = rotate(pos.direction, value); break;
		case 'L': pos.direction = rotate(pos.direction, -value); break;
		case 'N': pos.north += value; break;
		case 'S': pos.north -= value; break;
		case 'E': pos.west -= value; break;
		case 'W': pos.west += value; break;
	}
	return pos;
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
	coordinates position = { 0, 0, 'E' };

	for (int i = 0; i < data.size(); i++) {
		position = modifyPos(data[i], position);
	}
	cout << "N:" << position.north << "W:" << position.west
		 << "Sum:" << abs(position.north) + abs(position.west);

	output.close();

	return 56;
}