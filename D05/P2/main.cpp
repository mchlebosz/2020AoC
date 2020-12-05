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
	vector<pair<int, int>> seats;
	int maxRow;
	int minRow;
	int maxCol;
	int minCol;
	for (int i = 0; i < data.size(); i++) {
		maxRow = 127;
		minRow = 0;
		maxCol = 7;
		minCol = 0;

		for (short r = 0; r < 7; r++) {
			if (data[i][r] == 'F') maxRow -= ceil((maxRow - minRow) / 2.0);
			if (data[i][r] == 'B') minRow += ceil((maxRow - minRow) / 2.0);
		}
		for (short c = 7; c < 10; c++) {
			if (data[i][c] == 'L') maxCol -= ceil((maxCol - minCol) / 2.0);
			if (data[i][c] == 'R') minCol += ceil((maxCol - minCol) / 2.0);
		}
		seats.push_back(make_pair(minRow, minCol));
	}

	vector<int> seatid(0);
	for (int i = 0; i < seats.size(); i++) {
		seatid.push_back(seats[i].first * 8 + seats[i].second);
	}
	sort(seatid.begin(), seatid.end());

	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < seatid.size() - 1; i++) {
		if (seatid[i] != seatid[i + 1] - 1)
			output << "missing: " << seatid[i] + 1;
	}
	// for all seats
	// for (auto x : seatid) output << x << "\n";

	output.close();

	return 56;
}