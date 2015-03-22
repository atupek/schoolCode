//
//  gamePlay.cpp
//  checkers
//
//  Created by annietupek on 2/23/14.
//  Copyright (c) 2014 annietupek. All rights reserved.
//

#include "gamePlay.h"
#include <algorithm>
using std::swap;

// print out the board
void printBoard(myBoard &Board)
{
    for (auto i=0; i<64; i++)
    {
        if (i%8==7)
        {
            Board[i].printSquare();
            cout << endl;
        }
        else
        {
            Board[i].printSquare();
        }
    }
}

// set the inital board
void setInitialBoard(myBoard &Board)
{
    for (auto i=0; i<=7; i++)
    {
        if (i%2==1)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = false;
            Board[i].kingPiece = false;
        }
    }
    for (auto i=8; i<=15; i++)
    {
        if (i%2==0)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = false;
            Board[i].kingPiece = false;
        }
    }
    for (auto i=16; i<=23; i++)
    {
        if (i%2==1)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = false;
            Board[i].kingPiece = false;
        }
    }
    for (auto i=24; i<=31; i++)
    {
        if (i%2==0)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = true;
        }
    }
    for (auto i=32; i<=39; i++)
    {
        if (i%2==1)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = true;
        }
    }
    for (auto i=40; i<=47; i++)
    {
        if (i%2==0)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = true;
            Board[i].kingPiece = false;
        }
    }
    for (auto i=48; i<=55; i++)
    {
        if (i%2==1)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = true;
            Board[i].kingPiece = false;
        }
    }
    for (auto i=56; i<=63; i++)
    {
        if (i%2==0)
        {
            Board[i].unusedSquare = true;
            Board[i].emptySquare = false;
        }
        else
        {
            Board[i].emptySquare = false;
            Board[i].myPiece = true;
            Board[i].kingPiece = false;
        }
    }
    printBoard(Board);
}

//check for legal move
bool moveLegal(myBoard &Board, int from, int to)
{
    if (!Board[to].emptySquare)
    {
        return false;//can't move to a non-empty square
    }
    else if (Board[from].emptySquare)
    {
        return false;//can't move a piece from an empty square
    }
    else if (Board[from].myPiece)//for mypieces
    {
        if (!Board[from].kingPiece) //if it's not a king piece
        {
            if ((to == (from-9)) || (to == (from -7)))
                return true;
            else if (!Board[from-9].unusedSquare && !Board[from-9].emptySquare && !Board[from-9].myPiece && (to == (from-16) || to == (from-18)))
            {
                return true;
            }
            else if (!Board[from-7].unusedSquare && !Board[from-7].emptySquare && !Board[from-7].myPiece && (to == (from-14) || to == (from-16)))
            {
                return true;
            }
        }
        else if (Board[from].kingPiece) //if it is a king piece
        {
            if ((to == (from-9)) || (to == (from -7)) || (to == (from+9)) || (to == (from+7)))
                return true;
            else if (!Board[from-9].unusedSquare && !Board[from-9].emptySquare && !Board[from-9].myPiece && (to == (from-16) || to == (from-18)))
            {
                return true;
            }
            else if (!Board[from+9].unusedSquare && !Board[from+9].emptySquare && !Board[from+9].myPiece && (to == (from+16) || to == (from+18)))
            {
                return true;
            }
            else if (!Board[from-7].unusedSquare && !Board[from-7].emptySquare && !Board[from-7].myPiece && (to == (from-14) || to == (from-16)))
            {
                return true;
            }
            else if (!Board[from+7].unusedSquare && !Board[from+7].emptySquare && !Board[from+7].myPiece && (to == (from+14) || to == (from+16)))
            {
                return true;
            }
        }
    }
    else if (!Board[from].myPiece)//for opponent's pieces
    {
        if (!Board[from].kingPiece) //if it's not a king piece
        {
            if ((to == (from+9)) || (to == (from +7)))
                return true;
            else if (!Board[from+9].unusedSquare && !Board[from+9].emptySquare && Board[from+9].myPiece && (to == (from+16) || to == (from+18)))
            {
                return true;
            }
            else if (!Board[from+7].unusedSquare && !Board[from+7].emptySquare && Board[from+7].myPiece && (to == (from+14) || to == (from+16)))
            {
                return true;
            }
        }
        else if (Board[from].kingPiece) //if it is a king piece
        {
            if ((to == (from-9)) || (to == (from -7)) || (to == (from+9)) || (to == (from+7)))
                return true;
            else if (!Board[from-9].unusedSquare && !Board[from-9].emptySquare && Board[from-9].myPiece && (to == (from-16) || to == (from-18)))
            {
                return true;
            }
            else if (!Board[from+9].unusedSquare && !Board[from+9].emptySquare && Board[from+9].myPiece && (to == (from+16) || to == (from+18)))
            {
                return true;
            }
            else if (!Board[from-7].unusedSquare && !Board[from-7].emptySquare && Board[from-7].myPiece && (to == (from-14) || to == (from-16)))
            {
                return true;
            }
            else if (!Board[from+7].unusedSquare && !Board[from+7].emptySquare && Board[from+7].myPiece && (to == (from+14) || to == (from+16)))
            {
                return true;
            }
        }
    }
    
    cout << "Illegal move" << endl;
    return false;
}

//force jump over opponent's piece
void forceJump(myBoard &Board, int from)
{
    if (!Board[from+7].unusedSquare && !Board[from+7].emptySquare &&
        !Board[from+7].myPiece)
    {
        if(Board[from+14].emptySquare)
        {
            swap(Board[from],Board[from+14]);
        }
        else if(Board[from+16].emptySquare)
        {
            swap(Board[from],Board[from+16]);
        }
    }
    else if (!Board[from+9].unusedSquare && !Board[from+9].emptySquare &&
             !Board[from+9].myPiece)
    {
        if(Board[from+16].emptySquare)
        {
            swap(Board[from],Board[from+16]);
        }
        else if(Board[from+18].emptySquare)
        {
            swap(Board[from],Board[from+18]);
        }
    }
}

//move piece
void movePiece(myBoard &Board, int from, int to)
{
    if (moveLegal(Board, from, to))
    {
        if (to == (from-16) || to == (from-18))
        {
            removePiece(Board, (from-9));
            swap(Board[from], Board[to]);
        }
        else if (to == (from-14) || to == (from-16))
        {
            removePiece(Board, (from-7));
            swap(Board[from], Board[to]);
        }
        else if (to == (from+16) || to == (from+18))
        {
            removePiece(Board, (from+9));
            swap(Board[from], Board[to]);
        }
        else if (to == (from+14) || to == (from+16))
        {
            removePiece(Board, (from+7));
            swap(Board[from], Board[to]);
        }
        else
        {
           swap(Board[from], Board[to]); 
        }
    }
    else
    {
        //cout << "Illegal move" << endl;
    }
}

//remove piece
void removePiece(myBoard &Board, int jumped)
{
    Board[jumped].emptySquare = true;
}

//set piece to king
void setKing(myBoard &Board, int coord)
{
    Board[coord].kingPiece = true;
}