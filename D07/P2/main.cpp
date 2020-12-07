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

struct bag {
	vector<int> parentId;
	string color;
	vector<pair<int, int> > child;
};

string trim(const string& str) {
	size_t first = str.find_first_not_of(' ');
	if (string::npos == first) { return str; }
	size_t last = str.find_last_not_of(' ');
	return str.substr(first, (last - first + 1));
};

void printbags(vector<bag> Bags) {
	for (int i = 0; i < Bags.size(); i++) {
		cout << "[ ";
		for (int j = 0; j < Bags[i].parentId.size(); j++) {
			cout << Bags[i].parentId[j] << ", ";
		}
		cout << "] ";

		cout << Bags[i].color;

		cout << "[ ";

		for (int j = 0; j < Bags[i].child.size(); j++) {
			cout << "{" << Bags[i].child[j].first << ", "
				 << Bags[i].child[j].second << "},";
		}
		cout << "]\n";
	}
}

int countContainBags(vector<bag> Bags, int parent_index) {
	int sum = 1;
	if (Bags[parent_index].child.size() == 0) { return 1; }
	for (int i = 0; i < Bags[parent_index].child.size(); i++) {
		sum += Bags[parent_index].child[i].second *
			   countContainBags(Bags, Bags[parent_index].child[i].first);
	}
	return sum;
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

	vector<bag> Bags;
	for (int i = 0; i < data.size(); i++) {
		string currBag   = data[i].substr(0, data[i].find("bags contain") + 13);
		string parentBag = currBag.substr(0, currBag.find("bags") - 1);

		vector<string> childs(0);
		// fill childs with childs strings
		while (currBag.length() > 0) {
			// cout << currBag << "\n";
			int prevIndex = data[i].find(currBag) + currBag.length();
			int nextIndex = data[i].find("bag", prevIndex) + 5;

			currBag = string(data[i].begin() + prevIndex,
							 data[i].begin() + nextIndex);

			childs.push_back(trim(currBag.substr(0, currBag.length() - 5)));
			if (nextIndex + 1 >= data[i].length()) break;
		}
		// cout << parentBag << " : ";
		// cout << parentBag << "\n";
		int Parentindex = -5;
		// finding Parent index
		for (int j = 0; j < Bags.size(); j++) {
			if (Bags[j].color == parentBag) { Parentindex = j; }
		}
		// if parent not exist create
		if (Parentindex == -5) {
			bag newBag;
			newBag.color = parentBag;
			Parentindex  = Bags.size();
			Bags.push_back(newBag);
		}
		// cout << Parentindex << "\n";
		// cout << childs[0] << ";\n";
		// finding childs
		// cout << childs.size() << "-" << Bags.size() << "\n";
		for (int c = 0; c < childs.size(); c++) {
			for (int j = 0; j <= Bags.size(); j++) {
				// if it is no other bag
				if ((int)childs[c][0] - (int)'0' == 62)
					break;
				else {
					// if bag doesnt exist
					if (j == Bags.size()) {
						// create bag
						bag newChildBag;
						// add name
						newChildBag.color = childs[c].substr(2);
						// add parent index
						newChildBag.parentId.push_back(Parentindex);
						// add this to table
						Bags.push_back(newChildBag);
						// add child to parent;
						Bags[Parentindex].child.push_back(
							make_pair(j, (int)childs[c][0] - (int)'0'));
						break;
						// if bag exists
					} else if (Bags[j].color == childs[c].substr(2)) {
						// add parent info to bag
						Bags[j].parentId.push_back(Parentindex);
						// add child info to bag

						Bags[Parentindex].child.push_back(
							make_pair(j, (int)childs[c][0] - (int)'0'));
						break;
					}
				}
			}
		}
	}

	ofstream output;
	output.open("output.txt");
	for (int i = 0; i < Bags.size(); i++) {
		output << "[ ";
		for (int j = 0; j < Bags[i].parentId.size(); j++) {
			output << Bags[i].parentId[j] << ", ";
		}
		output << "] ";

		output << Bags[i].color;

		output << " [ ";

		for (int j = 0; j < Bags[i].child.size(); j++) {
			output << "{" << Bags[i].child[j].first << ", "
				   << Bags[i].child[j].second << "},";
		}
		output << "]\n";
	}

	int Shiny = 0;
	for (int i = 0; i < Bags.size(); i++) {
		if (Bags[i].color == "shiny gold") { Shiny = i; }
	}

	cout << countContainBags(Bags, Shiny) - 1 << "\n";

	// correct ans 222;

	output.close();

	return 56;
}