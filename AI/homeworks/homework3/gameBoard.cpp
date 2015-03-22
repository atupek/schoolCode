//
//  gameBoard.cpp
//  checkers
//
//  Created by annietupek on 2/22/14.
//  Copyright (c) 2014 annietupek. All rights reserved.
//

#include "gameBoard.h"
#include <iostream>
using std::cout;
using std::endl;


//default ctor, creates emtpy square
Square::Square() : emptySquare(0), myPiece(0), kingPiece(0), unusedSquare(0)
{}

//print Square
void Square::printSquare()
{
    if (emptySquare==true)
    {
        cout << " |";
    }
    else if (unusedSquare==true)
    {
        cout << "X|";
        
    }
    else if (emptySquare==false && myPiece==false)
    {
        if (kingPiece==false)
        {
        cout << "o|";
        }
        else if (kingPiece == true)
        {
            cout << "O|";
        }
        
    }
    else if(emptySquare==false && myPiece == true)
    {
        if (kingPiece == false)
        {
        cout << "m|";
        }
        else if (kingPiece==true)
        {
            cout << "M|";
        }
    }
}