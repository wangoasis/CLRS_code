Topological sort algorithm of a directed acylic graph:
A topological sort of a directed acylic graph is a linear ordering of all its vertices such that if G contains an edge (u, v) ( u points to v), then u appears before v in the ordering. (If the graph contains a cycle, then no linear ordering is possible.)

```
Topological-sort(G):
    call DFS(G) to compute finishing times f[v] for each vertex v;
    as each vertex is finished, insert it onto the front of a linked list;
    return the linked list;
```
