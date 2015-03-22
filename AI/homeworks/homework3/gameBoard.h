//
//  gameBoard.h
//  checkers
//
//  Created by annietupek on 2/22/14.
//  Copyright (c) 2014 annietupek. All rights reserved.
//

#ifndef checkers_gameBoard_h
#define checkers_gameBoard_h

class Square
{
public:
    bool myPiece; //1 if true
    bool kingPiece; //1 if true
    bool emptySquare; //1 if true
    bool unusedSquare; //1 if true
    
    void printSquare(); //print square
    //default ctor
    Square();
};

#endif
