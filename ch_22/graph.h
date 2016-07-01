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
typedef enum { WHITE, GRAY, BLACK } color_type;

void DFS_visit(vertex*, 
               int*, 
               map<vertex*, color_type>&,
               map<vertex*, vertex*>,
               map<vertex*, int>,
               map<vertex*, int>);

void BFS(graph& g, vertex* start)
{
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

void DFS(graph& g)
{
    map<vertex*, color_type> color;
    map<vertex*, vertex*> parent;
    map<vertex*, int> start;
    map<vertex*, int> finish;
    for (auto iter = g.begin(); iter != g.end(); iter++)
    {
        color[*iter] = WHITE;
        parent[*iter] = nullptr;
    }
    int time = 0;
    for (auto iter = g.begin(); iter != g.end(); iter++)
        if (color[*iter] == WHITE)
            DFS_visit(*iter, &time, color, parent, start, finish);
}

void DFS_visit(vertex* u, 
               int* time, 
               map<vertex*, color_type>& color,
               map<vertex*, vertex*> parent,
               map<vertex*, int> start,
               map<vertex*, int> finish)
{
    color[u] = GRAY;
    (*time)++;
    start[u] = *time;
    for (auto iter = u->linked_vertex.begin(); 
         iter != u->linked_vertex.end();
         iter++)
    {
        if (color[*iter] == WHITE)
        {
            parent[*iter] = u;
            DFS_visit(*iter, time, color, parent, start, finish);
        }
    }
    color[u] = BLACK;
    (*time)++;
    finish[u] = *time;
    std::cout << u->name << " " << start[u] << " " << finish[u] << std::endl;
}
#endif
