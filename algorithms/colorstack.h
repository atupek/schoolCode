// Ann Tupek
// CS 611
// Homework 5
// Due 20 Nov 2014

// Header for colorstack.cpp

#ifndef colorstack_H
#define colorstack_H


#include <vector>
using std::vector;

// typedef Block as a vector of ints
typedef vector<int> Block;

//prototype for colorStack
int colorStack(const vector<Block> & blocks, int requiredHeight);

#endif