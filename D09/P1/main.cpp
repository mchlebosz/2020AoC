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

bool hasProperty(vector<unsigned long long> arr, int curr, int pre) {
	for (int i = curr - pre; i < curr - 1; i++) {
		unsigned long long first   = arr[i];
		unsigned long long looking = arr[curr] - first;
		for (int j = i; j < curr; j++) {
			if (arr[j] == looking) return true;
		}
	}
	return false;
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
	int pre = 25;
	vector<unsigned long long> numbers;
	for (int i = 0; i < data.size(); i++) {
		numbers.push_back(stoll(data[i], nullptr, 10));
	}
	for (int i = pre; i < numbers.size(); i++) {
		if (!hasProperty(numbers, i, pre)) {
			cout << numbers[i] << " I:" << i;
			break;
		}
	}

	ofstream output;

	output.close();

	return 56;
}