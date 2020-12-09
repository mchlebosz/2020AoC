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

int sumsUp(vector<unsigned long long> arr, unsigned long long value,
		   int start) {
	unsigned long long sum = 0;
	for (int i = start; i < arr.size(); i++) {
		sum += arr[i];
		if (sum == value) return i;
		if (sum > value) return -1;
	}
	return -1;
}

unsigned long long findMax(vector<unsigned long long> arr,
						   unsigned long long start, unsigned long long stop) {
	unsigned long long max = arr[stop];
	for (int i = start; i <= stop; i++) {
		if (arr[i] > max) max = arr[i];
	}

	return max;
}
unsigned long long findMin(vector<unsigned long long> arr,
						   unsigned long long start, unsigned long long stop) {
	unsigned long long min = arr[start];
	for (int i = start; i < stop; i++) {
		if (arr[i] < min) min = arr[i];
	}

	return min;
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
	unsigned long long found;
	int indexF;
	for (int i = pre; i < numbers.size(); i++) {
		if (!hasProperty(numbers, i, pre)) {
			found  = numbers[i];
			indexF = i;
			cout << found << " I:" << i << "\n";
			break;
		}
	}
	int maxIndex = -1;
	int minIndex;
	for (int start = 0; start < indexF; start++) {
		maxIndex = sumsUp(numbers, found, start);
		if (maxIndex > 0) {
			minIndex = start;
			break;
		}
	}
	cout << "MinIndex = " << minIndex << "Maxindex = " << maxIndex << "\n";

	unsigned long long Max = findMax(numbers, minIndex, maxIndex);
	unsigned long long Min = findMin(numbers, minIndex, maxIndex);

	cout << "Min:" << Min << "; Max:" << Max << "\n";
	cout << Max + Min;

	ofstream output;

	output.close();

	return 56;
}