#include "Graph.h"
#include <string>
#include <fstream>
#include <iostream>
#include <regex>
#include <unordered_set>

int solution1(std::ifstream& file);
int solution2(std::ifstream& file);
std::string ltrim(const std::string& s);
std::string rtrim(const std::string& s);
std::string trim(const std::string& s);

int main() {
	// open file
	const std::string filename = "rules.txt";
	std::ifstream file(filename);
	if (!file) {
		std::cout << "Unable to open file." << std::endl;
		return 1;
	}

	// print solution
	std::cout << "Solution: " << solution2(file) << std::endl;

	// close file
	file.close();

	return 0;
}

int solution1(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	// create graph
	Graph graph;

	// for each rule external bag may contain internal bags:
	std::string rule;
	while (std::getline(file, rule)) { // read rule from file until no rules left
		// extract externalBag from rule
		std::string externalBag;
		externalBag = rule.substr(0, rule.find(" bags contain"));

		// if there are no internal bags, continue.
		if (rule.find("no other bags.") != std::string::npos) continue;

		// for each internal bag in rule:
		std::smatch internalBags;
		std::regex r("[a-z ]*[,.]");
		while (std::regex_search(rule, internalBags, r)) {
			std::string internalBag = internalBags[0];
			internalBag = internalBag.substr(0, internalBag.length() - 5);
			internalBag = trim(internalBag);
			graph.insertEdge(internalBag, externalBag);
			rule = internalBags.suffix().str();
		}
	}

	// perform DFS starting from "shiny gold" bag 
	// and count number of unique vertices visited
	std::unordered_set<std::size_t> visitedVertices;
	std::string source = "shiny gold";

	graph.dfs(
		source,
		[&visitedVertices](Edge edge) { visitedVertices.emplace(edge.dest); }
	);

	// return total number of unique vertices reachable from source
	return visitedVertices.size(); // don't count the gold bag itself
}

int solution2(std::ifstream& file) {
	// go to beginning of file
	file.clear();
	file.seekg(0, std::ios::beg);

	// create weighted graph
	Graph graph;

	// for each rule external bag may contain internal bags:
	std::string rule;
	while (std::getline(file, rule)) { // read rule from file until no rules left
		// extract externalBag from rule
		std::string externalBag;
		externalBag = rule.substr(0, rule.find(" bags contain"));

		// if there are no internal bags, continue.
		if (rule.find("no other bags.") != std::string::npos) continue;

		// for each internal bag in rule:
		std::smatch internalBags;
		std::regex r("[0-9]* [a-z ]*[,.]");
		while (std::regex_search(rule, internalBags, r)) {
			std::string internalBag = internalBags[0];
			internalBag = internalBag.substr(0, internalBag.length() - 5);
			internalBag = trim(internalBag);
			int weight = stoi(internalBag.substr(0, internalBag.find(" ")));
			internalBag = internalBag.substr(internalBag.find(" "), internalBag.length());
			internalBag = trim(internalBag);

			// add edge from externalBag to internalBag with weight
			graph.insertEdge(externalBag, internalBag, weight);
			rule = internalBags.suffix().str();
		}
	}

	// perform DFS on graph and count total weights
	return graph.solve2("shiny gold");
}

const std::string WHITESPACE = " \n\r\t\f\v";

std::string ltrim(const std::string& s)
{
	size_t start = s.find_first_not_of(WHITESPACE);
	return (start == std::string::npos) ? "" : s.substr(start);
}

std::string rtrim(const std::string& s)
{
	size_t end = s.find_last_not_of(WHITESPACE);
	return (end == std::string::npos) ? "" : s.substr(0, end + 1);
}

std::string trim(const std::string& s)
{
	return rtrim(ltrim(s));
}