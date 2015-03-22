// Ann Tupek
// CS 611
// Homework 2
// 30 September 2014
// Due 02 October 2014

// Header for colorStack.cpp

#ifndef colorStack_H
#define colorStack_H


#include <vector>
using std::vector;

// typedef Block as a vector of ints
typedef vector<int> Block;

//prototype for colorStack
int colorStack(const vector<Block> & blocks, int requiredHeight);

#endif