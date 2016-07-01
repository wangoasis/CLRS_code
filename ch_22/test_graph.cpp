#include "graph.h"

graph example;
vertex r('r'), s('s'), t('t'), u('u'), v('v'), w('w'), x('x'), y('y');

void init_graph()
{
    r.linked_vertex.push_back(&s);
    r.linked_vertex.push_back(&v);
    s.linked_vertex.push_back(&r);
    s.linked_vertex.push_back(&w);
    t.linked_vertex.push_back(&w);
    t.linked_vertex.push_back(&x);
    t.linked_vertex.push_back(&u);
    u.linked_vertex.push_back(&t);
    u.linked_vertex.push_back(&x);
    u.linked_vertex.push_back(&y);
    v.linked_vertex.push_back(&r);
    w.linked_vertex.push_back(&s);
    w.linked_vertex.push_back(&t);
    w.linked_vertex.push_back(&x);
    x.linked_vertex.push_back(&w);
    x.linked_vertex.push_back(&t);
    x.linked_vertex.push_back(&u);
    x.linked_vertex.push_back(&y);
    y.linked_vertex.push_back(&u);
    y.linked_vertex.push_back(&x);
    example.push_back(&r);
    example.push_back(&s);
    example.push_back(&t);
    example.push_back(&u);
    example.push_back(&v);
    example.push_back(&w);
    example.push_back(&x);
    example.push_back(&y);
}

int main()
{
    init_graph();
    BFS(example, &s);
}
