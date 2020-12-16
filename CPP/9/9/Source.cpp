#include <queue>
#include <string>
#include <iostream>
#include <fstream>
#include <unordered_set>

std::size_t solution1(std::ifstream& file);
std::size_t solution2(std::ifstream& file);
bool isSubsetSum(const std::unordered_set<std::size_t>& set, std::size_t sum);


int main() {
	// open the file
	const std::string filename = "code.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	// output the solution
	std::cout << solution2(file) << std::endl;

	// close the file
	file.close();
	return 0;
}

std::size_t solution1(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	std::queue<std::size_t> queue;
	std::unordered_set<std::size_t> set;

	// read first 25 numbers (preamble):
	int number;
	for (int i = 0; i < 25; i++) {
		file >> number;
		queue.push(number);
		set.emplace(number);
	}

	// for each number after the preamble:
	while (file >> number) {
		// check if number is not the sum of 2 of the past 25 numbers
		if (!isSubsetSum(set, number)) return number;

		// move the set up 1 in the sequence
		set.erase(queue.front());
		set.emplace(number);

		// move the queue up 1 in the sequence
		queue.pop();
		queue.push(number);
	}

	return -1;
}

std::size_t solution2(std::ifstream& file) {
	std::size_t target = solution1(file);

	// set file to beginning
	file.clear();
	file.seekg(0, std::ios::beg);

	// load numbers into vector
	std::vector<std::size_t> numbers;
	std::size_t number;
	while (file >> number) {
		numbers.push_back(number);
	}

	// Beginning at each number, try to build sequence
	std::size_t sum = 0;
	for (int i = 0; i < numbers.size(); i++) {
		sum = 0;
		for (int j = i; j < numbers.size() && sum <= target; j++) {
			sum += numbers[j];
			if (sum > target) break;
			if (sum == target) return numbers[i] + numbers[j-1];
		}
	}

	return 0;
}

bool isSubsetSum(const std::unordered_set<std::size_t>& set, std::size_t sum) {
	for (std::size_t number : set) {
		if (number == sum / 2.) continue; // don't count duplicates
		if (set.count(sum - number) != 0) return true;
	}
	return false;
}