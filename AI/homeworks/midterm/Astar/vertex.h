//  Ann Tupek
//  vertex.h
//  Astar
//  CS 405
//  Midterm
//

#ifndef __Astar__vertex__
#define __Astar__vertex__

#include <iostream>
#include <queue>
using std::priority_queue;
#include <utility>
using std::pair;
#include <vector>
using std::vector;
using std::swap;

class Vertex
{
public:
    int vertexID;
    vector <pair<int, int> > neighbors;
    Vertex(int i);
    Vertex();
    Vertex(Vertex const & v);
    Vertex operator = (const Vertex & rhs);
    friend bool operator ==(const Vertex & lhs, const Vertex & rhs);
    friend bool operator < (const Vertex & lhs, const Vertex & rhs);
};


#endif /* defined(__Astar__vertex__) */
