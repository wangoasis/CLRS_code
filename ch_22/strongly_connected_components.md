decomposing a directed graph into its strongly connected components.

```
STRONGLY_CONNECTED_COMPONENTS(G):
    call DFS(G) to compute finishing times f[u] for each vertex u;
    compute transpose of graph G, GT
    call DFS(GT), but in the main loop of DFS, consider the vertices
in order of decreasing f[u] (as computed in line 1)
    output the vertices of each tree in the depth-first forest formed in line 3 as a separate strongly connected component
```
