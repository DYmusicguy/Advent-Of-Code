#pragma once
#include <unordered_map>
#include <vector>
#include <functional>

struct Edge {
	std::size_t src;
	std::size_t dest;
	int weight;
};

class Graph
{
private:
	std::unordered_map<std::string, std::size_t> dict;
	std::vector<std::vector<Edge>> adjacencyList;
	std::size_t vertexCount = 0;

public:
	Graph() {}

	void insertVertex(const std::string& name);
	void insertEdge(const std::string& src, const std::string& dest, const int weight=0);
	void insertEdge(const std::size_t src, const std::size_t dest, const int weight=0);
	void insertEdge(const Edge edge);

	bool containsVertex(const std::string& name) const;
	const std::vector<std::size_t> getNeighbors(const std::size_t vertex) const;
	const std::vector<Edge>& getEdges(const std::size_t vertex) const;

	void dfs(const std::string& source, std::function<void(Edge edge)> foo) const;
	void dfs(const std::size_t source, std::function<void(Edge edge)> foo) const;

	int solve2(const std::string& source) const;
	int solve2(const std::size_t source) const;
};