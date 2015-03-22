//
//  gamePlay.h
//  checkers
//
//  Created by annietupek on 2/22/14.
//  Copyright (c) 2014 annietupek. All rights reserved.
//

#ifndef checkers_gamePlay_h
#define checkers_gamePlay_h

#include "gameBoard.h"
#include <vector>
using std::vector;
#include <iostream>
using std::cout;
using std::endl;

//typedef the vector of Squares
typedef vector <Square> myBoard;

void printBoard(myBoard &Board);
void setInitialBoard(myBoard &Board);
bool moveLegal(myBoard &Board, int from, int to);
void forceJump(myBoard &Board, int from);
void movePiece(myBoard &Board, int from, int to);
void removePiece(myBoard &Board, int jumped);
void setKing(myBoard &Board, int coord);

#endif
