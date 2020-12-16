#include <vector>
#include <iostream>
#include <string>
#include <fstream>
#include <unordered_set>
#include <utility>

struct Command {
	std::string name;
	int value;
};

int solution1(const std::vector<Command>& commands);
int solution2(const std::vector<Command>& commands);

std::pair<int, int> simulateProgram(const std::vector<Command>& commands);

int main() {
	// open file
	const std::string filename = "program.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Could not open file." << std::endl;
		return 1;
	}

	// read commands from file into vector
	char name[4];
	int value;
	std::vector<Command> commands;
	while (!file.eof()) {
		file >> name >> value;
		commands.push_back(Command({ name, value }));
	}

	// simulate execution of program until command is repeated, and print value in accumulator
	std::cout << solution2(commands) << std::endl;

	// close file
	file.close();

	return 0;
}

int solution1(const std::vector<Command>& commands) {
	return simulateProgram(commands).first;
}

int solution2(const std::vector<Command>& commands) {
	std::vector<Command> copy = commands;

	// for each command of type nop or jump:
	for (Command& command : copy) {
		if (command.name == "acc") {
			continue;
		}
		else if (command.name == "nop" || command.name == "jmp") {
			// swap the type from nop to jump or vice versa
			command.name = (command.name == "jmp" ? "nop" : "jmp");
			
			// simulate the execution of the new program
			std::pair<int, int> simulationResult = simulateProgram(copy);

			// if the program terminates, return the accumulator value
			if (simulationResult.second == copy.size()) return simulationResult.first;

			// swap the type back for continued execution
			command.name = (command.name == "jmp" ? "nop" : "jmp");
		}
		else {
			std::cout << "Illegal command encountered: " << command.name << std::endl;
			return -1;
		}
	}

	return -1;
}

std::pair<int, int> simulateProgram(const std::vector<Command>& commands) {
	int pc = 0, acc = 0; // program counter, accumulator
	std::unordered_set<int> visitedCommands; // keep track of commands we have visited

	// simulate execution of program
	while (visitedCommands.count(pc) == 0 && pc < commands.size()) {
		visitedCommands.emplace(pc);
		if (commands[pc].name == "nop") {
			pc++;
		}
		else if (commands[pc].name == "acc") {
			acc += commands[pc].value;
			pc++;
		}
		else if (commands[pc].name == "jmp") {
			pc += commands[pc].value;
		}
	}

	return std::pair<int, int>(acc, pc);
}