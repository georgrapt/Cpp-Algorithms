//Giorgos Raptakis
//Assignment 10

#define _USE_MATH_DEFINES
#include <vector>
#include <iostream>
#include <cstdlib>
#include <math.h>
#include <fstream>
#include <algorithm>
#include <stdlib.h>
#include <ctime>
#include <queue>

#include "Vertex.h"
#include "Edge.h"
#include "Graph.h"

using namespace std;

void EdgesInVertex(Graph &);
void print_vertices(Edge *);
void print_adjacent_edges(Vertex *);
vector<Vertex* > neighboring_Vertex(Vertex* );
//void Closest_neighb_Vertex(Vertex* v, Vertex*& name,int &weight);
void Dijkstra(Vertex*, Graph &);
void printDijkstra(Graph &);
bool smallerX(Edge* pt1, Edge* pt2);
Vertex* neighbor_ofaVertex(Vertex* v, int weighted);

struct CompareVertices
{
	bool operator ()(Vertex* v1, Vertex* v2)
	{
		return v1->shortest_distance > v2->shortest_distance;
	}
};

int main()
{
	Vertex* v0 = new Vertex(0);
	Vertex* v1 = new Vertex(1);
	Vertex* v2 = new Vertex(2);
	Vertex* v3 = new Vertex(3);
	Vertex* v4 = new Vertex(4);
	Vertex* v5 = new Vertex(5);
	Vertex* v6 = new Vertex(6);
	Vertex* v7 = new Vertex(7);
	Vertex* v8 = new Vertex(8);

	Edge* e0 = new Edge(0, v0, v1, 4);
	Edge* e1 = new Edge(1, v1, v2, 8);
	Edge* e2 = new Edge(2, v2, v3, 7);
	Edge* e3 = new Edge(3, v3, v4, 9);
	Edge* e4 = new Edge(4, v4, v5, 10);
	Edge* e5 = new Edge(5, v5, v6, 2);
	Edge* e6 = new Edge(6, v6, v7, 1);
	Edge* e7 = new Edge(7, v7, v8, 7);
	Edge* e8 = new Edge(8, v8, v6, 6);
	Edge* e9 = new Edge(9, v8, v2, 2);
	Edge* e10 = new Edge(10, v2, v5, 4);
	Edge* e11 = new Edge(11, v5, v3, 14);
	Edge* e12 = new Edge(12, v7, v0, 8);
	Edge* e13 = new Edge(13, v7, v1, 11);

	Graph g;
	g.vertices.push_back(v0);
	g.vertices.push_back(v1);
	g.vertices.push_back(v2);
	g.vertices.push_back(v3);
	g.vertices.push_back(v4);
	g.vertices.push_back(v5);
	g.vertices.push_back(v6);
	g.vertices.push_back(v7);
	g.vertices.push_back(v8);

	g.edges.push_back(e0);
	g.edges.push_back(e1);
	g.edges.push_back(e2);
	g.edges.push_back(e3);
	g.edges.push_back(e4);
	g.edges.push_back(e5);
	g.edges.push_back(e6);
	g.edges.push_back(e7);
	g.edges.push_back(e8);
	g.edges.push_back(e9);
	g.edges.push_back(e10);
	g.edges.push_back(e11);
	g.edges.push_back(e12);
	g.edges.push_back(e13);

	//print_vertices(e0);

	EdgesInVertex(g);
	//print_adjacent_edges(v5);

	Dijkstra(v0, g);
	printDijkstra(g);

	system("PAUSE");
	return 0;
}


// FUNCTIONS' IMPLEMENTATION //
void printDijkstra(Graph &g) {
	for (auto n : g.vertices) {
		cout << "The vertex: " << n->label << " has shortest distance: " << n->shortest_distance << endl;
	}
}

void Dijkstra(Vertex* StartVertex, Graph &g) {

	priority_queue<Vertex*, vector<Vertex*>, CompareVertices> pq;

	StartVertex->shortest_distance = 0;
	pq.push(StartVertex);

	while (!pq.empty()) {
		Vertex* top = pq.top();
		pq.pop();
		
		top->used = true;

		for (auto n : top->listedges) {
		
			Vertex* Sec;
			int Weight_Dist=n->weighted;

			//Call function which return the second vertex
			Sec= neighbor_ofaVertex(top, Weight_Dist); 

			if (Sec->shortest_distance > top->shortest_distance + Weight_Dist) {
				Sec->shortest_distance = top->shortest_distance + Weight_Dist;
				if (!(Sec->used)) {
					pq.push(Sec);
				}
			}
		}
	}
}

Vertex* neighbor_ofaVertex(Vertex* v, int Weigh){
	Vertex* ve=0;

	for (auto n : v->listedges) {
		if ((n->last->label == v->label) && (n->weighted== Weigh)) {
			ve = n->start;
		}
		else if ((n->start->label == v->label) && (n->weighted == Weigh)) {
			ve = n->last;
		}	
	}
	return ve;
}


void EdgesInVertex(Graph &g) {
	for (auto edge : g.edges) {
		int lab_Start = edge->start->label;//verticies name which is an int
		int  lab_Last = edge->last->label;
		//lab_Start as name by luck can be used as a pointer in the vertex for the position
		g.vertices.at(lab_Start)->listedges.push_back(edge);
		g.vertices.at(lab_Last)->listedges.push_back(edge);
	}

}

void print_adjacent_edges(Vertex *v) {
	cout << "\n The list of edges in Vertex " << v->label << " is: \t";

	for (auto n : v->listedges) {
		cout << (*n).labelEdge << " \t ";
	}
	cout << "\n" << endl;
}
