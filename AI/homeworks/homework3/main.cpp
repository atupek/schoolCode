//
//  main.cpp
//  checkers
//
//  Created by annietupek on 2/22/14.
//  Copyright (c) 2014 annietupek. All rights reserved.
//

#include <iostream>
#include "gameBoard.h"
#include "gamePlay.h"
#include <vector>
using std::vector;


int main()
{
    myBoard Board (64);
    setInitialBoard(Board);
    cout << endl;
    movePiece(Board, 16, 25);
    printBoard(Board);
    cout << endl;
    movePiece(Board, 25, 16);
    printBoard(Board);
    cout << endl;
    movePiece(Board, 43, 34);
    printBoard(Board);
    
    return 0;
}

