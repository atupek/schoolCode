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
    cout << "16, 25" << endl;
    printBoard(Board);
    cout << endl;
    //setKing(Board, 25); //setting king works
    movePiece(Board, 25, 16);//illegal move if not king, with king is legal, works.
    cout << "25, 16" << endl;
    printBoard(Board);
    cout << endl;
    movePiece(Board, 43, 34);
    cout << "43, 34" << endl;
    printBoard(Board);
    movePiece(Board, 25, 43);//this should be a legal move! Problem is here.  Fix it!
    cout << "25, 43" << endl;
    printBoard(Board);
    
    return 0;
}