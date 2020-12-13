#include <iostream>
#include <string>
#include <fstream>
#include <iostream>

struct Rule {
	char c;
	size_t min;
	size_t max;
};

bool isValidPassword1(const std::string password, const Rule& rule);
bool isValidPassword2(const std::string password, const Rule& rule);
int solve1(std::ifstream& file);
int solve2(std::ifstream& file);
Rule extractRule(std::string ruleText);

int main() {
	// open passwords file
	const std::string filename = "passwords.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open file!" << std::endl;
		return 1;
	}

	int count = solve2(file);
	std::cout << "Valid Passwords: " << count << std::endl;

	return 0;
}

bool isValidPassword1(const std::string password, const Rule& rule) {
	size_t count = std::count(password.begin(), password.end(), rule.c);
	return count >= rule.min && count <= rule.max;
}

bool isValidPassword2(const std::string password, const Rule& rule) {
	return (password[rule.min - 1] == rule.c) != (password[rule.max - 1] == rule.c);
}

int solve1(std::ifstream& file) {
	int result = 0;
	std::string line;

	while (!file.eof()) {
		std::getline(file, line);
		
		// split line into rule and password
		size_t endOfRule = line.find_last_of(' ');
		std::string ruleText = line.substr(0, endOfRule);
		std::string password = line.substr(endOfRule + 1, line.length());

		// get rule from ruleText
		Rule rule = extractRule(ruleText);

		// check if password follows rule
		if (isValidPassword1(password, rule)) {
			result++;
		}
	}

	return result;
}

int solve2(std::ifstream& file) {
	int result = 0;
	std::string line;

	while (!file.eof()) {
		std::getline(file, line);

		// split line into rule and password
		size_t endOfRule = line.find_last_of(' ');
		std::string ruleText = line.substr(0, endOfRule);
		std::string password = line.substr(endOfRule + 1, line.length());

		// get rule from ruleText
		Rule rule = extractRule(ruleText);

		// check if password follows rule
		if (isValidPassword2(password, rule)) {
			result++;
		}
	}

	return result;
}

Rule extractRule(std::string ruleText) {
	// split ruleText into numRange and charText
	size_t endOfRuleText = ruleText.find(' ');
	std::string numRange = ruleText.substr(0, endOfRuleText);
	std::string charText = ruleText.substr(endOfRuleText + 1, ruleText.length());

	// extract minCount and maxCount
	size_t ruleMin = std::stoi(numRange.substr(0, numRange.find('-')));
	size_t ruleMax = std::stoi(numRange.substr(numRange.find('-') + 1, numRange.length()));

	// extract rule char
	char ruleChar = charText[0];

	return Rule{ ruleChar, ruleMin, ruleMax };
}