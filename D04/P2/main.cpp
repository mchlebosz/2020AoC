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
			if (arr[i].find("byr") != std::string::npos) {
				int byear =
					stoi(arr[i].substr(arr[i].find("byr") + 4, 4), nullptr, 10);
				if (byear >= 1920 && byear <= 2002) { byr = 1; }
				cout << byear << ":" << byr << "\n";
			}

			if (arr[i].find("iyr") != std::string::npos) {
				int iyear =
					stoi(arr[i].substr(arr[i].find("iyr") + 4, 4), nullptr, 10);
				if (iyear >= 2010 && iyear <= 2020) { iyr = 1; }
			}

			if (arr[i].find("eyr") != std::string::npos) {
				int eyear =
					stoi(arr[i].substr(arr[i].find("eyr") + 4, 4), nullptr, 10);
				if (eyear >= 2020 && eyear <= 2030) eyr = 1;
			}
			if (arr[i].find("hgt") != std::string::npos) {
				string height = arr[i].substr(arr[i].find("hgt") + 4, 4);
				if (height[3] == 'c') {
					if (stoi(height.substr(0, 3), nullptr, 10) >= 150 &&
						stoi(height.substr(0, 3), nullptr, 10) <= 193) {
						hgt = 1;
					}
				}
				if (height[3] == 'n') {
					if (stoi(height.substr(0, 2), nullptr, 10) >= 59 &&
						stoi(height.substr(0, 2), nullptr, 10) <= 76) {
						hgt = 1;
					}
				}
			}

			if (arr[i].find("hcl") != std::string::npos) {
				string haircolor = arr[i].substr(arr[i].find("hcl") + 4, 7);
				if (haircolor[0] == '#') {
					bool corrletters = true;
					for (short i = 1; i < haircolor.length(); i++) {
						if ((int)haircolor[i] < 103) { hcl = 1; }
					}
				}
			}
			if (arr[i].find("ecl") != std::string::npos) {
				string eye = arr[i].substr(arr[i].find("ecl") + 4, 3);
				if (eye == "amb" || eye == "blu" || eye == "brn" ||
					eye == "gry" || eye == "grn" || eye == "hzl" ||
					eye == "oth") {
					ecl = 1;
				}
			}

			if (arr[i].find("pid") != std::string::npos) {
				int idpos  = arr[i].find("pid") + 4;
				int amount = 0;
				while ((int)arr[i][idpos] > 47 && (int)arr[i][idpos] < 58) {
					amount++;
					idpos++;
				}
				if (amount = 9) { pid = 1; }
			}
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