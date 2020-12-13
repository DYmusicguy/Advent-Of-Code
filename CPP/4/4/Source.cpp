#include <iostream>
#include <fstream>
#include <string>
#include <unordered_map>
#include <vector>
#include <algorithm>
#include <regex>
#include <unordered_set>

int solve1(std::ifstream& file);
int solve2(std::ifstream& file);
std::string readLine(std::ifstream& file);
bool containsAllTags(const std::string& line);
bool isValidPassport(const std::string& line);
std::vector<std::string> split(const std::string& str, char delim);

int main() {
	// open file
	const std::string filename = "passports.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	std::cout << "Solution: " << solve2(file) << std::endl;

	return 0;
}

int solve1(std::ifstream& file) {
	int result = 0;
	while (!file.eof()) {
		std::string line = readLine(file);

		if (containsAllTags(line)) result++;
	}

	return result;
}

int solve2(std::ifstream& file) {
	int result = 0;
	while (!file.eof()) {
		std::string line = readLine(file);

		if (isValidPassport(line)) {
			
			result++;
		}
		else {
			std::cout << "line: " << line << std::endl;
		}
	}

	return result;
}

bool containsAllTags(const std::string& line) {
	std::string tags[7] = { "byr", "iyr", "eyr", "hgt", "hcl", "ecl", "pid" };

	// check if line contains all of the tags
	for (int i = 0; i < 7; i++) {
		if (line.find(tags[i]) == std::string::npos) return false;
	}

	return true;
}

// read lines from file until empty line is read
std::string readLine(std::ifstream& file) {
	std::string result = "";
	std::string line;
	while (getline(file, line) && line != "") {
		std::replace(line.begin(), line.end(), ' ', ',');
		result += line + ',';
	}
	return result.substr(0, result.length() - 1); // ignore last comma
}

bool isValidPassport(const std::string& line) {
	// make sure all relevant tags are present
	if (!containsAllTags(line)) return false;

	// extract key value pairs from line
	std::vector<std::string> keyValuePairs = split(line, ',');
	std::unordered_map<std::string, std::string> map;

	// add key value pairs to map
	for (std::string keyValuePairText : keyValuePairs) {
		std::vector<std::string> keyValuePair = split(keyValuePairText, ':');
		map.emplace(std::make_pair(keyValuePair[0], keyValuePair[1]));
	}

	// check for valid birth year
	if (map["byr"].length() != 4) return false;
	if (stoi(map["byr"]) < 1920 || stoi(map["byr"]) > 2002) return false;

	// check for valid issue year
	if (map["iyr"].length() != 4) return false;
	if (stoi(map["iyr"]) < 2010 || stoi(map["iyr"]) > 2020) return false;

	// check for valid experation year
	if (map["eyr"].length() != 4) return false;
	if (stoi(map["eyr"]) < 2020 || stoi(map["eyr"]) > 2030) return false;

	// check for valid height
	std::string heightType = map["hgt"].substr(map["hgt"].length() - 2, map["hgt"].length());
	int height = stoi(map["hgt"].substr(0, map["hgt"].length() - 2));
	if (heightType == "cm" && (height < 150 || height > 193)) return false;
	else if (heightType == "in" && (height < 59 || height > 76)) return false;
	else if (heightType != "cm" && heightType != "in") return false;

	// check for valid hair color
	if (!std::regex_match(map["hcl"], std::regex("^#[0-9a-f]{6}$"))) return false;

	// check for valid eye color
	std::unordered_set<std::string> validEyeColors({ "amb", "blu", "brn", "gry", "grn", "hzl", "oth" });
	if (validEyeColors.find(map["ecl"]) == validEyeColors.end()) return false;

	// check for valid passport id
	if (!std::regex_match(map["pid"], std::regex("^[0-9]{9}$"))) return false;

	return true;
}

std::vector<std::string> split(const std::string& str, char delim) {
	std::vector<std::string> strings;
	size_t start;
	size_t end = 0;
	while ((start = str.find_first_not_of(delim, end)) != std::string::npos) {
		end = str.find(delim, start);
		strings.push_back(str.substr(start, end - start));
	}
	return strings;
}