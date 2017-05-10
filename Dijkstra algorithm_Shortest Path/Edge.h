#pragma once
#include <list> //used for adjacency list (neighbors of a vertex)
using namespace std;
class Vertex;
class Edge {

public:
	int labelEdge;
	int weighted;
	Vertex *start;
	Vertex *last;

	//constructor
	Edge(int m_label,  Vertex *m_start, Vertex *m_last, int m_weighted );
	Edge() {}
};

Edge::Edge(int m_label,  Vertex *m_start, Vertex *m_last, int m_weighted)
{
	labelEdge = m_label;
	weighted = m_weighted;
	start = m_start;
	last = m_last;
}
