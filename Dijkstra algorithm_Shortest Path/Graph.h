#pragma once
#include <list> //used for adjacency list (neighbors of a vertex)
#include <vector>
using namespace std;
class Vertex;
class Edge;

class Graph {

public:
	vector<Edge *> edges;
	vector<Vertex *> vertices;
	//constructor
	Graph() {}
};
