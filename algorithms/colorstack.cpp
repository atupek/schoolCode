// Ann Tupek
// CS 611
// Homework 5
// Due 20 Nov 2014

// colorstack.cpp
// Implements BFS for determining best weight of a stack of blocks,
// where each block can be stacked on the one beneath it only if
// its bottom color matches the previous block's top color
// Dynamic Programming revision

#include "colorstack.h"
#include <iostream>

#include <climits> // for INT_MAX

using std::tuple;

// typedef the tuple of blocks to keep track of the current block
// and the increasing height & weight of the stack of blocks
typedef tuple<Block, int, int> BlockNScore;

// for colors, height, & weight indices of Block, a vector of ints
const int BOTTOM = 0;
const int TOP = 1;
const int HEIGHT = 2;
const int WEIGHT = 3;

int numColors;

vector<vector<int> > bestWeightTable;

//recursive helper function for colorStack
int colorStackR(const vector<Block> & blocks, int requiredHeight, int topColor)
{
    if(bestWeightTable[requiredHeight][topColor] != -1)
    {
        return bestWeightTable[requiredHeight][topColor];
    }
    int currentBest = INT_MAX;
    //for each block with that top color
    //if blockHeight >= requiredHeight
    //compare that block's weight to best weight, if better, then this is new best
    //o.w.
    //weight of using block = blockWeight + colorStackR(blocks, reqH-bloc's height, block's bottom color
    for(auto i = 0; i<blocks.size(); i++)
    {
        if(blocks[i][TOP] == topColor)
        {
            if(blocks[i][HEIGHT] >= requiredHeight)
            {
                if(blocks[i][WEIGHT] < currentBest)
                {
                    currentBest = blocks[i][WEIGHT];
                }
            }
            else
            {
                int tempWeight = colorStackR(blocks,
                                                    requiredHeight - blocks[i][HEIGHT],
                                                    blocks[i][BOTTOM]);
                if(tempWeight != INT_MAX)
                {
                    tempWeight += blocks[i][WEIGHT];
                    if(tempWeight < currentBest)
                    {
                        currentBest = tempWeight;
                    }
                }
            }
        }
    }
    bestWeightTable[requiredHeight][topColor]=currentBest;
    return currentBest;
}

// colorStack
// given a collection of blocks in vector form and a required height as an int
// returns the best weight for a stack of blocks of the required height
// returns -1 if no stack exists of the required height
int colorStack(const vector<Block> & blocks, int requiredHeight)
{
    //organize the colors so their index starts at 0
    int minColor = INT_MAX;
    int maxColor = 0;
    for(auto i = 0; i<blocks.size(); i++)
    {
        if(blocks[i][TOP] > maxColor)
        {
            maxColor = blocks[i][TOP];
        }
        if(blocks[i][BOTTOM] > maxColor)
        {
            maxColor = blocks[i][BOTTOM];
        }
        if(blocks[i][TOP] < minColor)
        {
            minColor = blocks[i][TOP];
        }
        if(blocks[i][BOTTOM] < minColor)
        {
            minColor = blocks[i][BOTTOM];
        }
    }
    numColors= maxColor-minColor +1;
    vector<Block> myBlocks = blocks;
    for(auto i = 0; i<myBlocks.size(); i++)
    {
        myBlocks[i][TOP] -= minColor;
        myBlocks[i][BOTTOM] -= minColor;
    }
    
    //initialize the table
    bestWeightTable.resize(requiredHeight+1);
    for(auto i=0; i<bestWeightTable.size(); i++)
    {
        bestWeightTable[i].resize(numColors);
        for(auto j=0; j<bestWeightTable[i].size(); j++)
        {
            bestWeightTable[i][j]=-1;
        }
    }
    
    int currentBest = INT_MAX;

    //find the best weight for given height for each color
    for(auto i = 0; i<numColors; i++)
    {
        int tempBest = colorStackR(myBlocks, requiredHeight, i);
        if (tempBest < currentBest)
        {
            currentBest = tempBest;
        }
    }

    if(currentBest == INT_MAX)
    {
        return -1;
    }
    else
    {
        return currentBest;
    }
}


