#include "Graph.h"
#include <vector>
#include <functional>
#include <iostream>

void Graph::insertVertex(const std::string& name) {
	dict.emplace(name, vertexCount);
	adjacencyList.push_back(std::vector<Edge>());
	adjacencyList[vertexCount] = std::vector<Edge>();
	vertexCount++;
}

void Graph::insertEdge(const std::string& src, const std::string& dest, const int weight) {
	if (!containsVertex(src)) insertVertex(src);
	if (!containsVertex(dest)) insertVertex(dest);
	insertEdge(Edge({ dict[src], dict[dest], weight }));
}

void Graph::insertEdge(const std::size_t src, const std::size_t dest, const int weight) {
	insertEdge(Edge({ src, dest, weight }));
}

void Graph::insertEdge(const Edge edge) {
	adjacencyList[edge.src].push_back(edge);
}

bool Graph::containsVertex(const std::string& name) const {
	return dict.count(name) != 0;
}

const std::vector<std::size_t> Graph::getNeighbors(std::size_t vertex) const {
	std::vector<std::size_t> result;
	for (Edge e : adjacencyList[vertex]) result.push_back(e.dest);
	return result;
}

const std::vector<Edge>& Graph::getEdges(std::size_t vertex) const {
	return adjacencyList[vertex];
}

void Graph::dfs(const std::string& source, std::function<void(Edge edge)> foo) const {
	dfs(dict.at(source), foo);
}

void Graph::dfs(const std::size_t source, std::function<void(Edge edge)> foo) const {
	for (Edge edge : getEdges(source)) {
		foo(edge);
		dfs(edge.dest, foo);
	}
}

int Graph::solve2(const std::string& source) const {
	return solve2(dict.at(source));
}

int Graph::solve2(const std::size_t source) const {
	int result = 0;
	for (Edge edge : getEdges(source)) {
		result += edge.weight + edge.weight * solve2(edge.dest);
	}
	return result;
}