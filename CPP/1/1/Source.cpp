#include <iostream>
#include <unordered_set>
#include <string>
#include <fstream>
#include <vector>

bool solve1(const std::vector<int>& numbers, int& num1, int& num2);
bool solve2(const std::vector<int>& numbers, int& num1, int& num2, int& num3);


int main()
{
	// open file
	std::string filename = "numbers.txt";
	std::ifstream file(filename);

	// read numbers from file into vector
	std::vector<int> numbers;
	int num;
	while (!file.eof()) {
		file >> num;
		numbers.push_back(num);
	}

	// call solve
	int num1, num2, num3;
	bool wasSuccessful = solve2(numbers, num1, num2, num3);

	// print result
	if (wasSuccessful) {
		std::cout << "solution: " << num1 * num2 * num3 << std::endl;
	}
	else {
		std::cout << "No pair found." << std::endl;
	}


	file.close();
	return 0;
}

bool solve1(const std::vector<int>& numbers, int& num1, int& num2) {
	std::unordered_set<int> set;

	for (int x : numbers) {
		// check if the complement of x has already been found
		if (set.find(2020 - x) != set.end()) {
			num1 = x;
			num2 = 2020 - x;
			return true;
		}
		set.emplace(x);
	}

	return false;
}

bool solve2(const std::vector<int>& numbers, int& num1, int& num2, int& num3) {
	std::unordered_set<int> set;
	for (int x : numbers) {
		set.emplace(2020 - x);
	}

	for (int x1 : numbers) {
		for (int x2 : numbers) {
			if (x1 == x2) continue;
			if (set.find(x1 + x2) != set.end()) {
				num1 = x1;
				num2 = x2;
				num3 = 2020 - (x1 + x2);
				return true;
			}
		}
	}
	return false;
}