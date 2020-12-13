#include <iostream>
#include <string>
#include <fstream>
#include <cmath>
#include <algorithm>
#include <unordered_set>
#include <limits>

int calculateSeatID(const std::string& boardingPass);
int solve1(std::ifstream& file);
int solve2(std::ifstream& file);

int main() {
	const std::string filename = "boarding_passes.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	std::cout << "Result: " << solve2(file) << std::endl;

	return 0;
}

int calculateSeatID(const std::string& boardingPass) {
	// calculate row
	int row = 0;
	for (char c : boardingPass.substr(0, 7)) {
		row <<= 1;
		if (c == 'B') row++;
	}

	// calculate column
	int col = 0;
	for (char c : boardingPass.substr(7, 10)) {
		col <<= 1;
		if (c == 'R') col++;
	}

	// calculate seat number
	return row * 8 + col;
}

int solve1(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	int result = 0;
	std::string line;
	while (file >> line) {
		result = std::max(result, calculateSeatID(line));
	}

	return result;
}

int solve2(std::ifstream& file) {
	std::unordered_set<int> set;
	int minID = INT_MAX, maxID = 0;

	// add seat ids to hashset
	file.clear();
	file.seekg(0, std::ios::beg);
	std::string line;
	while (file >> line) {
		int seatID = calculateSeatID(line);
		minID = std::min(minID, seatID);
		maxID = std::max(maxID, seatID);
		set.emplace(calculateSeatID(line));
	}

	// look for seat id that is missing
	file.clear();
	file.seekg(0, std::ios::beg);
	for (int i = minID + 1; i < maxID - 1; i++) {
		if (set.find(i) == set.end()) return i;
	}

	return -1;
}