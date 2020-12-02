#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

bool meetCriteria(string password, char letter, int min, int max) {
	if ((password[min - 1] == letter || password[max - 1] == letter) &&
		password[max - 1] != password[min - 1])
		return true;
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
	// open file for writing
	struct Password {
		int min;
		int max;
		char letter;
		string password;
	};
	vector<Password> passwords;
	for (int i = 0; i < data.size(); i++) {
		int min = stoi(data[i].substr(0, data[i].find('-')), nullptr, 10);
		int max = stoi(data[i].substr(data[i].find('-') + 1, data[i].find(' ')),
					   nullptr, 10);
		char letter        = data[i][data[i].find(':') - 1];
		string password    = data[i].substr(data[i].find(':') + 2);
		Password curr_pass = { min, max, letter, password };
		passwords.push_back(curr_pass);
	}

	ofstream output;
	output.open("output.txt");
	int amount = 0;
	for (int i = 0; i < passwords.size(); i++) {
		bool criteria = meetCriteria(passwords[i].password, passwords[i].letter,
									 passwords[i].min, passwords[i].max);
		if (criteria) amount++;
	}
	output << amount;

	output.close();

	return 0;
}