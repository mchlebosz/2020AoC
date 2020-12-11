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

int adjacentSeats(vector<string> arr, int y, int x) {
	int sum = 0;
	for (int i = -1; i <= 1; i++) {
		for (int j = -1; j <= 1; j++) {
			if (!(i == 0 && j == 0)) {
				if (y + i < arr.size() && y + i >= 0 && x + j >= 0 &&
					x + j < arr[y].length()) {
					if (arr[y + i][x + j] == '#') sum++;
				}
			}
		}
	}
	return sum;
}

vector<string> setupSeats(vector<string> oldarr) {
	vector<string> arr = oldarr;

	for (int i = 0; i < arr.size(); i++) {
		for (int j = 0; j < arr[i].length(); j++) {
			if (oldarr[i][j] == '.') arr[i][j] = '.';
			int adjacent = adjacentSeats(oldarr, i, j);
			if (oldarr[i][j] == 'L' && adjacent == 0) arr[i][j] = '#';
			if (oldarr[i][j] == '#' && adjacent >= 4) arr[i][j] = 'L';
			// cout << adjacent;
		}
		// cout << "\n";
	}
	return arr;
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
	vector<string> newvector = data;
	vector<string> oldvector = data;
	do {
		oldvector = newvector;
		newvector = setupSeats(newvector);

		// for (int i = 0; i < newvector.size(); i++) {
		// 	cout << newvector[i] << "\n";
		// }
		// cout << "\n\n";

	} while (newvector != oldvector);

	ofstream output;
	output.open("output.txt");

	int occupied = 0;
	for (int i = 0; i < newvector.size(); i++) {
		output << newvector[i] << "\n";
		for (int j = 0; j < newvector[i].length(); j++) {
			if (newvector[i][j] == '#') occupied++;
		}
	}
	output << "\n\n " << occupied;

	output.close();

	return 56;
}