//  Ann Tupek
//  vertex.cpp
//  Astar
//  CS 405
//  Midterm
//

#include "vertex.h"
Vertex::Vertex()
{
    vertexID=0;
}

Vertex::Vertex(int i)
{
    vertexID=i;
}

Vertex::Vertex(Vertex const &v)
{
    vertexID=v.vertexID;
    neighbors=v.neighbors;
}

bool operator < (const Vertex & lhs, const Vertex & rhs)
{
    return (lhs.vertexID<rhs.vertexID);
}

bool operator ==(const Vertex & lhs, const Vertex & rhs)
{
    return (lhs.vertexID==rhs.vertexID);
}

Vertex Vertex::operator=(const Vertex & other)
{
    vertexID=other.vertexID;
    neighbors=other.neighbors;
    return *this;
}
