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
	int mod = 1;
	// Check for right
	while (x + mod < arr[y].length() && arr[y][x + mod] != 'L') {
		if (arr[y][x + mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}

	// check for left
	mod = 1;
	while (x - mod >= 0 && arr[y][x - mod] != 'L') {
		if (arr[y][x - mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for top
	mod = 1;
	while (y - mod >= 0 && arr[y - mod][x] != 'L') {
		if (arr[y - mod][x] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for bottom
	mod = 1;
	while (y + mod >= arr.size() && arr[y + mod][x] != 'L') {
		if (arr[y + mod][x] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for left top
	mod = 1;
	while (x - mod >= 0 && y - mod >= 0 && arr[y - mod][x - mod] != 'L') {
		if (arr[y - mod][x - mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for right bottom
	mod = 1;
	while (x + mod < arr[y].length() && y + mod < arr.size() &&
		   arr[y + mod][x + mod] != 'L') {
		if (arr[y + mod][x + mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for top right
	mod = 1;
	while (x + mod < arr[y].length() && y - mod >= 0 &&
		   arr[y - mod][x + mod] != 'L') {
		if (arr[y - mod][x + mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}
	// check for bottom left
	mod = 1;
	while (x - mod >= 0 && y + mod < arr.size() &&
		   arr[y + mod][x - mod] != 'L') {
		if (arr[y + mod][x - mod] == '#') {
			sum++;
			break;
		}
		mod++;
	}

	return sum;
}

vector<string> setupSeats(vector<string> oldarr) {
	vector<string> arr = oldarr;
	int w              = 0;
	while (w < arr.size()) {
		for (int j = 0; j < oldarr[w].length(); ++j) {
			if (oldarr[w][j] == '.') arr[w][j] = '.';
			int adjacent = adjacentSeats(oldarr, w, j);
			if (oldarr[w][j] == 'L' && adjacent == 0) arr[w][j] = '#';
			if (oldarr[w][j] == '#' && adjacent >= 5) arr[w][j] = 'L';
			cout << adjacent;
		}
		cout << " : " << w << "\n";
		++w;
	}
	cout << arr.size();
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
		cout << newvector.size();

		for (int i = 0; i < newvector.size(); i++) {
			cout << newvector[i] << "\n";
		}
		cout << "\n\n";

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