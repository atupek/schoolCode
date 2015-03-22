// Ann Tupek
// CS 611
// Homework 2
// 30 September 2014
// Due 02 October 2014

// colorStack.cpp
// Implements BFS for determining best weight of a stack of blocks,
// where each block can be stacked on the one beneath it only if
// its bottom color matches the previous block's top color

#include "colorStack.h"
#include <iostream>

#include <tuple> // for tuple
using std::tuple;
using std::get;

#include <queue> // for queue
using std::queue;

#include <limits> // for INT_MAX

// typedef the tuple of blocks to keep track of the current block
// and the increasing height & weight of the stack of blocks
typedef tuple<Block, int, int> BlockNScore;

// for colors, height, & weight indices of Block, a vector of ints
const int BOTTOM = 0;
const int TOP = 1;
const int HEIGHT = 2;
const int WEIGHT = 3;

// colorStack
// given a collection of blocks in vector form and a required height as an int
// returns the best weight for a stack of blocks of the required height
// returns -1 if no stack exists of the required height
int colorStack(const vector<Block> & blocks, int requiredHeight)
{
    // set the bestWeight to max value of int (2147483647 on my system)
    int bestWeight = INT_MAX;
    
    // queue for BFS
    queue<BlockNScore> q;
    
    // put all the blocks in the queue with initial height & weight
    for (auto i=0; i<blocks.size(); ++i)
    {
        // make a tuple to store the Block, height, and weight
        BlockNScore initialBlock =
                make_tuple (blocks[i], blocks[i][HEIGHT], blocks[i][WEIGHT]);
        
        // add the block to the queue
        q.push(initialBlock);
    }
    
    // while there are still blocks in the queue get them
    // check to see if they can be added
    // until required height has been reached
    while(!q.empty())
    {
        // get block from the queue
        BlockNScore thisBlock = q.front();
        
        // remove block from the queue
        q.pop();
        
        // get its height & weight from the tuple BlockNScore
        int thisHeight = get<1>(thisBlock);
        int thisWeight = get<2>(thisBlock);
        
        // check to see the required height has been reached
        if(thisHeight >= requiredHeight)
        {
            // check to see if this stack has the lowest weight
            if(thisWeight <= bestWeight)
            {
                bestWeight = thisWeight;
            }
        }
        
        // if required height hasn't been reached, stack more blocks
        else
        {
            for(auto i=0; i<blocks.size(); ++i)
            {
                // check to see if top color of current block matches
                // bottom color of next block
                int thisTopColor = get<0>(thisBlock)[TOP];
                int nextBottomColor = blocks[i][BOTTOM];
                
                // if colors match, add height & weight of next block
                // to the stack of blocks and push new stack of blocks
                // into the queue
                if(thisTopColor == nextBottomColor)
                {
                    int newHeight = get<1>(thisBlock) + blocks[i][HEIGHT];
                    int newWeight = get<2>(thisBlock) + blocks[i][WEIGHT];
                    BlockNScore newBlock =
                        make_tuple (blocks[i], newHeight, newWeight);
                    q.push(newBlock);
                }
            }
        }
    }
    
    // if we didn't reach the required height, return -1
    if(bestWeight == INT_MAX)
    {
        return -1;
    }
    
    // if we've reached the required height, return best weight
    else
    {
        return bestWeight;
    }
}