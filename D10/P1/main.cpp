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
	vector<int> chargers(1, 0);
	for (int i = 0; i < data.size(); i++) {
		chargers.push_back(stoi(data[i], nullptr, 10));
	}
	sort(chargers.begin(), chargers.end());
	chargers.push_back(chargers[chargers.size() - 1] + 3);

	ofstream output;
	output.open("output.txt");
	int oneamount   = 0;
	int threeamount = 0;

	for (int i = 1; i < chargers.size(); i++) {
		if (chargers[i] - chargers[i - 1] == 1) oneamount++;
		if (chargers[i] - chargers[i - 1] == 3) threeamount++;
	}

	output << oneamount * threeamount;

	output.close();

	return 56;
}