//  Ann Tupek
//  main.cpp
//  Astar
//  CS 405
//  Midterm
//

#include "vertex.h"
#include <iostream>
#include <queue>
#include <vector>
#include <random>
#include <utility>
using std::priority_queue;
using std::queue;
using std::vector;
using std::mt19937;
using std::random_device;
using std::make_pair;
using std::pair;
using std::find;
using std::cout;
using std::endl;

int numVertices=5;//to change number of vertices in random graph, change this number

void Tree(int numVertices);

vector<int> aStar(Vertex start, Vertex goal, priority_queue<Vertex> vertices);

pair<int, int> costAndNode;

priority_queue<Vertex> vertexSet;

vector<int> path;

void displayPath(vector<int> vertexPath);

int main()
{
    Tree(numVertices);
    Vertex start = Vertex(1);//first vertex generated
    Vertex goal = Vertex (numVertices);//last vertex generated
    
    aStar(start, goal, vertexSet);
    displayPath(path);
    

    return 0;
}

//create 2-D array for tree's adjacency matrix
void Tree(int numVertices)
{
    int tree[numVertices][numVertices];
    for (auto i=0; i<numVertices; i++)
    {
        for (auto j=0; j<(numVertices); j++)
        {
            if (i==j)
            {
                tree[i][j]=0;//vertices are not adjacent to themselves
            }
            else
            {
                if (i<j)
                {
                    //randomly assign adjacency
                    random_device rd;
                    mt19937 generator(rd());
                    std::uniform_int_distribution<> distribution(0, 100);
                    {
                        if (distribution(generator)%2==0)
                        {
                            tree[i][j]=1;//adjacent
                        }
                        else
                        {
                            tree[i][j]=0;//not adjacent
                        }
                    }
                }
                else
                {
                    tree[i][j]=tree[j][i];//to reflect adjacency across i==j diagonal
                }
            }
            //std::cout << tree[i][j];//only if you want to see the adjacency matrix
            new Vertex(i);
        if (tree[i][j]==1)
        {
            int cost;
            random_device rd;
            mt19937 generator(rd());
            std::uniform_int_distribution<> distribution(0, 100);
            cost=(distribution(generator)%numVertices);
            costAndNode=make_pair(cost, j);
            Vertex(i).neighbors.push_back(costAndNode);
            vertexSet.push(Vertex(i));//put vertex into open set
        }
    }
    //std::cout << std::endl;//only if you want to see the adjacency matrix
}
}

void displayPath(vector<int> vertexPath)
{
    cout << "The path is: " << endl;
    for (auto i=vertexPath.begin(); i!=vertexPath.end(); i++)
    {
        cout << *i << ", ";
    }
}

//A* Search
vector<int> aStar(Vertex start, Vertex goal, priority_queue<Vertex> vertexSet)
{
    vector<Vertex> openSet;
    openSet.push_back(start);
    vector<Vertex> closedSet;
    int costOfVertex = 0; //g(n)
    int pathEstimate = 0; //h(n), since we don't have a heuristic estimate, set to 0
    int costOfPath = 0; //f(n) = g(n)+h(n)
    while (!openSet.empty())
    {
        Vertex current;
        current = openSet.front();
        if (current == goal)
        {
            path.push_back(current.vertexID);
            return path;
        }
        closedSet.push_back(current);
        while (!current.neighbors.empty())
        {
            Vertex neighbor;
            int ID;
            ID = current.neighbors.front().second;
            neighbor = Vertex(ID);
            if (neighbor == goal)
            {
                costOfVertex = costAndNode.first;
                costOfPath += costOfVertex;
                path.push_back(neighbor.vertexID);
                return path;
            }
            //if neighbor is not in closed set
            else if (find(closedSet.begin(), closedSet.end(), neighbor) != closedSet.end())
            {
                openSet.push_back(neighbor);
            }
            else
            {
                continue;
            }
            
        }
    }
    return path;
}


