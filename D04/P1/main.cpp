#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <vector>

std::vector<std::string> explode(std::string const& s, char delim) {
	std::vector<std::string> result;
	std::istringstream iss(s);

	for (std::string token; std::getline(iss, token, delim);) {
		result.push_back(std::move(token));
	}

	return result;
}

using namespace std;

int amounthasfields(vector<string> arr) {
	bool byr           = false;
	bool iyr           = false;
	bool eyr           = false;
	bool hgt           = false;
	bool hcl           = false;
	bool ecl           = false;
	bool pid           = false;
	int correct_amount = 0;
	for (int i = 0; i < arr.size(); i++) {
		if (arr[i] == "") {
			if (byr && iyr && eyr && hgt & hcl && ecl && pid) correct_amount++;

			byr = false;
			iyr = false;
			eyr = false;
			hgt = false;
			hcl = false;
			ecl = false;
			pid = false;

		} else {
			if (arr[i].find("byr") != std::string::npos) byr = 1;
			if (arr[i].find("iyr") != std::string::npos) iyr = 1;
			if (arr[i].find("eyr") != std::string::npos) eyr = 1;
			if (arr[i].find("hgt") != std::string::npos) hgt = 1;
			if (arr[i].find("hcl") != std::string::npos) hcl = 1;
			if (arr[i].find("ecl") != std::string::npos) ecl = 1;
			if (arr[i].find("pid") != std::string::npos) pid = 1;
		}
	}
	if (byr && iyr && eyr && hgt & hcl && ecl && pid) correct_amount++;

	return correct_amount;
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

	output << amounthasfields(data);

	output.close();

	return 0;
}