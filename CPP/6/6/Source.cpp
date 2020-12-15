#include <iostream>
#include <fstream>
#include <string>
#include <unordered_set>

std::size_t solution1(std::ifstream& file);
std::size_t solution2(std::ifstream& file);
std::size_t countUniqueAnswers(std::string line);

int main() {
	// open input file
	const std::string filename = "answers.txt";
	std::ifstream file(filename);

	// calculate and output the solution
	std::cout << "Solution: " << solution2(file) << std::endl;

	// close input file
	file.close();
}

std::size_t solution1(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	// extract group answers into single string
	std::size_t solution = 0;
	while (!file.eof()) {
		std::string groupAnswers;
		std::string line;
		while (getline(file, line) && line != "") {
			groupAnswers += line;
		}

		// add number of unique answers of current group to solution
		solution += countUniqueAnswers(groupAnswers);
	}

	// return sum of number of unique answers for each group
	return solution;
}

std::size_t solution2(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	// read file group by group
	size_t result = 0;
	while (!file.eof()) {
		std::string groupAnswers;
		std::string line;
		int numGroupMembers = 0;
		std::unordered_multiset<char> charMultiset;

		// combine all rows of the group into single string
		while (getline(file, line) && line != "") {
			groupAnswers += line;

			// count total number of people in current group
			numGroupMembers++;
		}

		// count up occurances of each letter
		for (char c : groupAnswers) charMultiset.insert(c);

		// count total number of letters where the number of occurances 
		// of that letter equals the number of people in the group
		for (char c = 'a'; c <= 'z'; c++) {
			if (charMultiset.count(c) == numGroupMembers) result++;
		}
	}
	return result;
}

std::size_t countUniqueAnswers(std::string line) {
	// add all characters in line to set
	std::unordered_set<char> set;
	for (char c : line) set.insert(c);

	// return number of unique characters found (size of set)
	return set.size();
}