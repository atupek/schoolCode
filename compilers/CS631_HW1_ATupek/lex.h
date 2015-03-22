/*
Ann Tupek
CS631
HW1
lex.h header for lex.cpp
*/
#ifndef LEX_H
#define LEX_H

typedef pair<char, int> Token;
extern vector<Token> tokens;

void lex(string program);
void match(const string & program, int & currentChar);

#endif