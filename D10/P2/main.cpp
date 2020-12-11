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

unsigned long long part2(vector<int> adapters) {
	int N = adapters.size();
	std::vector<int64_t> comb(N);

	comb[N - 1] = 1;
	for (int k = N - 2; k >= 0; k--)
		for (int i = k + 1; i < N && adapters[i] - adapters[k] <= 3; i++)
			comb[k] += comb[i];

	return comb[0];
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
	vector<int> chargers(1, 0);
	for (int i = 0; i < data.size(); i++) {
		chargers.push_back(stoi(data[i], nullptr, 10));
	}
	sort(chargers.begin(), chargers.end());
	chargers.push_back(chargers[chargers.size() - 1] + 3);

	ofstream output;
	output.open("output.txt");

	cout << part2(chargers);

	output.close();

	return 56;
}