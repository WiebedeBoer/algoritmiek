// algoritme2.cpp : This file contains the 'main' function. Program execution begins and ends there.
//The file search.cpp implements a labeled graph and a depth-first search algorithm. 
//Watch the video on depth - first and breadth - first search.Extend the search.cpp with an implementation of breadth - first search.
//Hint: As the video explains, the non - recursive implementation of breadth - first search is similar to the non - recursive implementation of depth - first search, but differs from it in two ways :
//it uses a queue(First In First Out) instead of a stack and
//it checks whether a vertex has been discovered before enqueueing the vertex rather than delaying this check until the vertex is dequeued from the queue.

#include "pch.h"
#include <iostream>

typename std::vector<Vertex>::const_iterator Graph::cbegin(Vertex v) const
{
	currentVertex = v;
	return adjacents[v].cbegin();
}

typename std::vector<Vertex>::const_iterator Graph::cend() const
{
	return adjacents[currentVertex].cend();
}

Graph::GraphMap Graph::adjacents = {
		{ 'S', { 'A', 'B' } },
		{ 'A', { 'B', 'D', 'S' } },
		{ 'B', { 'S', 'A', 'C' } },
		{ 'C', { 'B', 'E' } },
		{ 'D', { 'A', 'G' } },
		{ 'E', { 'C' } },
		{ 'G', { 'D' } }
};

Path dfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{
	std::stack<Path> queue;
	std::set<Vertex> visited;
	Path path;

	queue.push(path);
	while (!queue.empty()) {
		path = queue.top();
		queue.pop();

		Vertex last;
		if (path.size() == 0) {
			last = start;
		}
		else {
			last = path.back();
		}
		if (goalTest(last))
			return path; // path is a vector of Vertices

		if (visited.find(last) == visited.end()) {
			visited.insert(last);
			for (auto it = graph.cbegin(last); it != graph.cend(); it++) { // extend path with new Vertex
				Path n = path;
				n.push_back(*it);
				queue.push(n);
			}
		}
	}
	return Path(); // return empty path
}

Path bfs(const Graph &graph, const Vertex &start, std::function<bool(const Vertex &vertex)> goalTest)
{

}

int main()
{
	Graph graph;

	Vertex start = 'S';
	Vertex goal = 'G';

	Path path = dfs(graph, start, [&](Vertex v) { return (v == goal); });
	//    Path path = bfs(graph, start, [&](Vertex v) { return (v == goal); });

	std::cout << start << std::endl;
	for (auto it = path.cbegin(); it != path.cend(); it++)
	{
		std::cout << *it << std::endl;
	}

	return 0;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
