#pragma once
class Edge;
#include <limits>
#include <vector> //used for adjacency list (neighbors of a vertex)
using namespace std;

class Vertex{

public:
	int label;
	int shortest_distance= numeric_limits<int>::max();
	bool used = false;
	vector < Edge*> listedges; 
	//constructor
	Vertex(int no);


	Vertex() {}
};
Vertex::Vertex(int no)
{
	label = no;

}
