#include <iostream>
#include <fstream>
#include <iostream>

int solve1(std::ifstream& file);
unsigned int solve2(std::ifstream& file);
int treesHitOnSlope(std::ifstream& file, int right, int down);

int main()
{
	// open file
	const std::string filename = "map.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	std::cout << "Solution: " << solve2(file) << std::endl;

	file.close();
	return 0;
}

int solve1(std::ifstream& file) {
	return treesHitOnSlope(file, 3, 1);
}

unsigned int solve2(std::ifstream& file) {
	int rights[5] = { 1, 3, 5, 7, 1 };
	int downs[5] = { 1, 1, 1, 1, 2 };

	unsigned int result = 1;
	for (int i = 0; i < 5; i++) {
		result *= treesHitOnSlope(file, rights[i], downs[i]);
	}

	return result;
}

int treesHitOnSlope(std::ifstream& file, int right, int down) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	int result = 0;
	std::string line;
	int currRight = 0;

	file >> line;
	if (line[currRight] == '#') result++;
	while (!file.eof()) {
		// update currRight and currDown
		currRight = (currRight + right) % line.length();
		for (int i = 0; i < down; i++) file >> line;

		if (line[currRight] == '#') result++;
	}

	std::cout << "right: " << right << ", down: " << down << ") " << result << std::endl;
	return result;
}	