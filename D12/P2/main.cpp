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

struct coordinates {
	int north;
	int east;
};

coordinates moveShipToWaypoint(string data, coordinates currPos,
							   coordinates waypoint) {
	int max = stoi(data.substr(1), nullptr, 10);
	for (int i = 0; i < max; i++) {
		currPos.north += waypoint.north;
		currPos.east += waypoint.east;
	}
	return currPos;
}

coordinates rotateW(coordinates waypoint, int degree) {
	int temp;
	while (degree > 0) {
		temp           = waypoint.north;
		waypoint.north = -waypoint.east;
		waypoint.east  = temp;
		degree -= 90;
	}
	while (degree < 0) {
		temp           = waypoint.north;
		waypoint.north = waypoint.east;
		waypoint.east  = -temp;
		degree += 90;
	}
	return waypoint;
}

coordinates transformWaypoint(string data, coordinates waypoint) {
	char command = data[0];
	int value    = stoi(data.substr(1), nullptr, 10);
	switch (command) {
		case 'R': waypoint = rotateW(waypoint, value); break;
		case 'L': waypoint = rotateW(waypoint, -value); break;
		case 'N': waypoint.north += value; break;
		case 'S': waypoint.north -= value; break;
		case 'W': waypoint.east -= value; break;
		case 'E': waypoint.east += value; break;
	}
	return waypoint;
}

main() {
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
	coordinates position = { 0, 0 };
	coordinates waypoint = { 1, 10 };

	for (int i = 0; i < data.size(); i++) {
		if (data[i][0] == 'F') {
			position = moveShipToWaypoint(data[i], position, waypoint);
		} else {
			waypoint = transformWaypoint(data[i], waypoint);
		}
	}
	cout << "N:" << position.north << "W:" << position.east
		 << "Sum:" << abs(position.north) + abs(position.east);

	output.close();

	return 56;
}