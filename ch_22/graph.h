#ifndef _GRAPH_H
#define _GRAPH_H

#include <vector>
using std::vector;
#include <limits.h>
#include <map>
using std::map;
#include <iostream>
#include <queue>
using std::queue;

struct vertex
{
	char name;
	vector<vertex*> linked_vertex; 

	vertex(char s)
	: name(s), linked_vertex()
	{ }
};

typedef vector<vertex*> graph;

void BFS(graph& g, vertex* start)
{
	typedef enum { WHITE, GRAY, BLACK } color_type;

	map<vertex*, color_type> color;
	map<vertex*, int> distance;
	map<vertex*, vertex*> parent;
	queue<vertex*> q;

	for (auto iter = g.begin(); iter != g.end(); iter++)
	{
		if (*iter != start)
		{
			color[*iter] = WHITE;
			distance[*iter] = INT_MAX;
			parent[*iter] = nullptr;
		}
	}
	color[start] = GRAY;
	distance[start] = 0;
	parent[start] = nullptr;

	q.push(start);
	while (!q.empty())
	{
		vertex* u = q.front();
		q.pop();
		for (auto iter = u->linked_vertex.begin(); iter != u->linked_vertex.end(); iter++)
		{
			if (color[*iter] == WHITE)
			{
				color[*iter] = GRAY;
				distance[*iter] = distance[u] + 1;
				parent[*iter] = u;
				q.push(*iter);
			}
		}
		color[u] = BLACK;
		std::cout << u->name << " " << distance[u] << std::endl;
	}
}
#endif
